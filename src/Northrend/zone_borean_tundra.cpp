/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Group.h"
#include "ScriptedEscortAI.h"
#include "PassiveAI.h"
#include "Player.h"
#include "ScriptMgr.h"

enum Sinkhole
{
    GO_EXPLOSIVES_CART = 188160,
    NPC_SCOURGED_BURROWER = 26250,
    QUEST_PLUG_THE_SINKHOLES = 11897,
    SPELL_SET_CART = 46797,
    SPELL_EXPLODE_CART = 46799,
    SPELL_SUMMON_CART = 46798,
    SPELL_SUMMON_WORM = 46800,
};

class npc_sinkhole_kill_credit_groupquests : public CreatureScript
{
public:
    npc_sinkhole_kill_credit_groupquests() : CreatureScript("npc_sinkhole_kill_credit") { }

    struct npc_sinkhole_kill_credit_groupquestsAI : public NullCreatureAI
    {
        npc_sinkhole_kill_credit_groupquestsAI(Creature* creature) : NullCreatureAI(creature) { }

        uint32 phaseTimer;
        uint8  phase;
        ObjectGuid casterGuid;

        void Reset() override
        {
            phaseTimer = 30000;
            phase = 0;
            casterGuid.Clear();
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (phase || spell->Id != SPELL_SET_CART)
                return;

            Player* player = caster->ToPlayer();
            if (player && player->GetQuestStatus(QUEST_PLUG_THE_SINKHOLES) == QUEST_STATUS_INCOMPLETE)
            {
                phase = 1;
                phaseTimer = 0;
                casterGuid = caster->GetGUID();
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!phase)
                return;

            if (phaseTimer <= diff)
            {
                switch (phase)
                {
                case 1:
                    DoCast(me, SPELL_EXPLODE_CART, true);
                    DoCast(me, SPELL_SUMMON_CART, true);
                    if (GameObject* cart = me->FindNearestGameObject(GO_EXPLOSIVES_CART, 3.0f))
                        cart->SetUInt32Value(GAMEOBJECT_FACTION, 14);
                    phaseTimer = 3000;
                    phase = 2;
                    break;
                case 2:
                    if (GameObject* cart = me->FindNearestGameObject(GO_EXPLOSIVES_CART, 3.0f))
                        cart->UseDoorOrButton();
                    DoCast(me, SPELL_EXPLODE_CART, true);
                    phaseTimer = 3000;
                    phase = 3;
                    break;
                case 3:
                    DoCast(me, SPELL_EXPLODE_CART, true);
                    phaseTimer = 2000;
                    phase = 5; // @fixme: phase 4 is missing...
                    break;
                case 5:
                    DoCast(me, SPELL_SUMMON_WORM, true);
                    if (Unit* worm = me->FindNearestCreature(NPC_SCOURGED_BURROWER, 3.0f))
                    {
                        worm->SetUnitFlag(UNIT_FLAG_NOT_SELECTABLE);
                        worm->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                    }
                    phaseTimer = 1000;
                    phase = 6;
                    break;
                case 6:
                    DoCast(me, SPELL_EXPLODE_CART, true);
                    if (Unit* worm = me->FindNearestCreature(NPC_SCOURGED_BURROWER, 3.0f))
                    {
                        Unit::Kill(me, worm);
                        worm->RemoveDynamicFlag(UNIT_DYNFLAG_LOOTABLE);
                    }
                    phaseTimer = 2000;
                    phase = 7;
                    break;
                case 7:
                    DoCast(me, SPELL_EXPLODE_CART, true);
                    if (Player* player = ObjectAccessor::GetPlayer(*me, casterGuid))
                    {
                        if (Group* group = player->GetGroup())
                        {
                            group->DoForAllMembers([this, player](Player* member)
                            {
                                if (member->IsAtGroupRewardDistance(player))
                                {
                                    member->KilledMonster(me->GetCreatureTemplate(), me->GetGUID());
                                }
                            });
                        }
                        else
                        {
                            player->KilledMonster(me->GetCreatureTemplate(), me->GetGUID());
                        }
                        
                    }
                    phaseTimer = 5000;
                    phase = 8;
                    break;
                default:
                    CreatureAI::EnterEvadeMode();
                    break;
                }
            }
            else phaseTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sinkhole_kill_credit_groupquestsAI(creature);
    }
};

enum BerylSorcerer
{
    EVENT_FROSTBOLT = 1,
    EVENT_ARCANE_CHAINS = 2,
    NPC_LIBRARIAN_DONATHAN = 25262,
    NPC_CAPTURED_BERLY_SORCERER = 25474,
    SPELL_FROSTBOLT = 9672,
    SPELL_ARCANE_CHAINS = 45611,
    SPELL_ARCANE_CHAINS_CHARACTER_FORCE_CAST = 45625,
    SPELL_ARCANE_CHAINS_SUMMON_CHAINED_MAGE_HUNTER = 45626,
    SPELL_COSMETIC_ENSLAVE_CHAINS_SELF = 45631,
    SPELL_ARCANE_CHAINS_CHANNEL_II = 45735
};

class npc_beryl_sorcerer_groupquests : public CreatureScript
{
public:
    npc_beryl_sorcerer_groupquests() : CreatureScript("npc_beryl_sorcerer") { }

    struct npc_beryl_sorcerer_groupquestsAI : public CreatureAI
    {
        npc_beryl_sorcerer_groupquestsAI(Creature* creature) : CreatureAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {
            _playerGUID.Clear();
            _chainsCast = false;
        }

        void Reset() override
        {
            me->SetReactState(REACT_AGGRESSIVE);
            Initialize();
        }

        void JustEngagedWith(Unit* who) override
        {
            if (me->IsValidAttackTarget(who))
            {
                AttackStart(who);
            }

            _events.ScheduleEvent(EVENT_FROSTBOLT, 3000, 4000);
        }

        void SpellHit(Unit* unit, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_ARCANE_CHAINS && !_chainsCast)
            {
                if (Player* player = unit->ToPlayer())
                {
                    _playerGUID = player->GetGUID();
                    _chainsCast = true;
                    _events.ScheduleEvent(EVENT_ARCANE_CHAINS, 4000);
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
            {
                return;
            }

            _events.Update(diff);

            if (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_FROSTBOLT:
                    DoCastVictim(SPELL_FROSTBOLT);
                    _events.ScheduleEvent(EVENT_FROSTBOLT, 3000, 4000);
                    break;
                case EVENT_ARCANE_CHAINS:
                    if (me->HasAura(SPELL_ARCANE_CHAINS))
                    {
                        if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                        {
                            me->CastSpell(player, SPELL_ARCANE_CHAINS_CHARACTER_FORCE_CAST, TriggerCastFlags(TRIGGERED_FULL_MASK & ~TRIGGERED_IGNORE_AURA_INTERRUPT_FLAGS & ~TRIGGERED_IGNORE_CAST_ITEM));

                            if (Group* group = player->GetGroup())
                            {
                                group->DoForAllMembers([player](Player* member)
                                {
                                    if (member->IsAtGroupRewardDistance(player))
                                    {
                                        member->KilledMonsterCredit(NPC_CAPTURED_BERLY_SORCERER);
                                    }
                                });
                            }
                            else
                            {
                                player->KilledMonsterCredit(NPC_CAPTURED_BERLY_SORCERER);
                            }

                            me->DisappearAndDie();
                        }
                    }
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }

    private:
        EventMap   _events;
        ObjectGuid _playerGUID;
        bool       _chainsCast;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_beryl_sorcerer_groupquestsAI(creature);
    }
};

enum Nerubar
{
    NPC_WARSONG_PEON = 25270,
    QUEST_TAKEN_BY_THE_SCOURGE = 11611,
    SPELL_FREED_WARSONG_MAGE = 45526,
    SPELL_FREED_WARSONG_SHAMAN = 45527,
    SPELL_FREED_WARSONG_WARRIOR = 45514,
    SPELL_FREED_WARSONG_PEON = 45532
};

const uint32 nerubarVictims[3] = { SPELL_FREED_WARSONG_MAGE, SPELL_FREED_WARSONG_SHAMAN, SPELL_FREED_WARSONG_WARRIOR };

class npc_nerubar_victim_groupquests : public CreatureScript
{
public:
    npc_nerubar_victim_groupquests() : CreatureScript("npc_nerubar_victim") {}

    struct npc_nerubar_victim_groupquestsAI : public NullCreatureAI
    {
        npc_nerubar_victim_groupquestsAI(Creature* creature) : NullCreatureAI(creature) {}

        void JustDied(Unit* killer) override
        {
            if (!killer || killer->GetTypeId() != TYPEID_PLAYER)
            {
                return;
            }

            Player* player = killer->ToPlayer();
            uint8 uiRand = urand(0, 99);

            if (uiRand < 40)
            {
                if (Group* group = player->GetGroup())
                {
                    group->DoForAllMembers([player](Player* member)
                    {
                        if (member->IsAtGroupRewardDistance(player))
                        {
                            member->KilledMonsterCredit(NPC_WARSONG_PEON);
                        }
                    });
                }
                else
                {
                    player->KilledMonsterCredit(NPC_WARSONG_PEON);
                }

                player->CastSpell(me, SPELL_FREED_WARSONG_PEON, true);
            }
            else if (uiRand < 80)
            {
                player->CastSpell(me, nerubarVictims[urand(0, 2)], true);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_nerubar_victim_groupquestsAI(creature);
    }
};

enum Lurgglbr
{
    QUEST_ESCAPE_WINTERFIN_CAVERNS = 11570,
    GO_CAGE = 187369,
    SAY_START_1 = 0,
    SAY_START_2 = 1,
    SAY_END_1 = 2,
    SAY_END_2 = 3
};

class npc_lurgglbr_groupquests : public CreatureScript
{
public:
    npc_lurgglbr_groupquests() : CreatureScript("npc_lurgglbr") { }

    struct npc_lurgglbr_groupquestsAI : public npc_escortAI
    {
        npc_lurgglbr_groupquestsAI(Creature* creature) : npc_escortAI(creature) { }

        uint32 IntroTimer;
        uint32 IntroPhase;

        void Reset() override
        {
            if (!HasEscortState(STATE_ESCORT_ESCORTING))
            {
                IntroTimer = 0;
                IntroPhase = 0;
            }
        }

        void WaypointReached(uint32 waypointId) override
        {
            switch (waypointId)
            {
            case 0:
                IntroPhase = 1;
                IntroTimer = 2000;
                break;
            case 41:
                IntroPhase = 4;
                IntroTimer = 2000;
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (IntroPhase)
            {
                if (IntroTimer <= diff)
                {
                    switch (IntroPhase)
                    {
                    case 1:
                        if (Player* player = GetPlayerForEscort())
                            Talk(SAY_START_1, player);
                        IntroPhase = 2;
                        IntroTimer = 7500;
                        break;
                    case 2:
                        Talk(SAY_START_2);
                        IntroPhase = 3;
                        IntroTimer = 7500;
                        break;
                    case 3:
                        me->SetReactState(REACT_AGGRESSIVE);
                        IntroPhase = 0;
                        IntroTimer = 0;
                        break;
                    case 4:
                        Talk(SAY_END_1);
                        IntroPhase = 5;
                        IntroTimer = 8000;
                        break;
                    case 5:
                        if (Player* player = GetPlayerForEscort())
                            Talk(SAY_END_2, player);
                        IntroPhase = 6;
                        IntroTimer = 2500;
                        break;

                    case 6:
                        if (Player* player = GetPlayerForEscort())
                        {
                            if (Group* group = player->GetGroup())
                            {
                                group->DoForAllMembers([player](Player* member)
                                {
                                    if (member->IsAtGroupRewardDistance(player))
                                    {
                                        member->AreaExploredOrEventHappens(QUEST_ESCAPE_WINTERFIN_CAVERNS);
                                    }
                                });
                            }
                            else
                            {
                                player->AreaExploredOrEventHappens(QUEST_ESCAPE_WINTERFIN_CAVERNS);
                            }
                        }
                        IntroPhase = 7;
                        IntroTimer = 2500;
                        break;

                    case 7:
                        me->DespawnOrUnsummon();
                        IntroPhase = 0;
                        IntroTimer = 0;
                        break;
                    }
                }
                else IntroTimer -= diff;
            }
            npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lurgglbr_groupquestsAI(creature);
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_ESCAPE_WINTERFIN_CAVERNS)
        {
            if (GameObject* go = creature->FindNearestGameObject(GO_CAGE, 5.0f))
                go->UseDoorOrButton();

            if (npc_escortAI* pEscortAI = CAST_AI(npc_lurgglbr_groupquests::npc_lurgglbr_groupquestsAI, creature->AI()))
                pEscortAI->Start(true, false, player->GetGUID());

            creature->SetFaction(player->GetTeamId() == TEAM_ALLIANCE ? FACTION_ESCORTEE_A_PASSIVE : FACTION_ESCORTEE_H_PASSIVE);
            return true;
        }
        return false;
    }
};

enum Khunok
{
    NPC_ORPHANED_MAMMOTH_CALF = 25861,
    SPELL_MAMMOTH_CALF_ESCORT_CREDIT = 46231,
    QUEST_KHU_NOK_WILL_KNOW = 11878
};

class npc_khunok_the_behemoth_groupquests : public CreatureScript
{
public:
    npc_khunok_the_behemoth_groupquests() : CreatureScript("npc_khunok_the_behemoth") { }

    struct npc_khunok_the_behemoth_groupquestsAI : public ScriptedAI
    {
        npc_khunok_the_behemoth_groupquestsAI(Creature* creature) : ScriptedAI(creature) { }

        void MoveInLineOfSight(Unit* who) override

        {
            ScriptedAI::MoveInLineOfSight(who);

            if (who->GetTypeId() != TYPEID_UNIT)
                return;

            if (who->GetEntry() == NPC_ORPHANED_MAMMOTH_CALF && me->IsWithinDistInMap(who, 10.0f))
            {
                if (Unit* owner = who->GetOwner())
                {
                    if (owner->GetTypeId() == TYPEID_PLAYER)
                    {
                        owner->CastSpell(owner, SPELL_MAMMOTH_CALF_ESCORT_CREDIT, true);
                        who->ToCreature()->DespawnOrUnsummon();

                        if (Player* player = owner->ToPlayer())
                        {
                            if (Group* group = player->GetGroup())
                            {
                                group->DoForAllMembers([player](Player* member)
                                {
                                    if (member != player)
                                    {
                                        if (member->IsAtGroupRewardDistance(player))
                                        {
                                            if (member->GetQuestStatus(QUEST_KHU_NOK_WILL_KNOW) == QUEST_STATUS_INCOMPLETE)
                                            {
                                                member->CompleteQuest(QUEST_KHU_NOK_WILL_KNOW);
                                            }
                                        }
                                    }
                                });
                            }
                        }
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_khunok_the_behemoth_groupquestsAI(creature);
    }
};

void AddSC_zone_borean_tundra_groupquests()
{
    new npc_sinkhole_kill_credit_groupquests();
    new npc_beryl_sorcerer_groupquests();
    new npc_nerubar_victim_groupquests();
    new npc_lurgglbr_groupquests();
    new npc_khunok_the_behemoth_groupquests();
}
