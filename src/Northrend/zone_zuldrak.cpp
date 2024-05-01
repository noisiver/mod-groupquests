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
#include "PassiveAI.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptMgr.h"
#include "SpellScript.h"

enum DrakuruShackles
{
    NPC_RAGECLAW = 29686,
    QUEST_TROLLS_IS_GONE_CRAZY = 12861,
    SPELL_LEFT_CHAIN = 59951,
    SPELL_RIGHT_CHAIN = 59952,
    SPELL_UNLOCK_SHACKLE = 55083,
    SPELL_FREE_RAGECLAW = 55223
};

class npc_drakuru_shackles_groupquests : public CreatureScript
{
public:
    npc_drakuru_shackles_groupquests() : CreatureScript("npc_drakuru_shackles") {}

    struct npc_drakuru_shackles_groupquestsAI : public NullCreatureAI
    {
        npc_drakuru_shackles_groupquestsAI(Creature* creature) : NullCreatureAI(creature)
        {
            _rageclawGUID.Clear();
            timer = 0;
        }

        void Reset() override
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void UpdateAI(uint32 diff) override
        {
            timer += diff;
            if (timer >= 2000)
            {
                timer = 0;
                if (_rageclawGUID)
                    return;

                if (Creature* cr = me->FindNearestCreature(NPC_RAGECLAW, 10.0f))
                {
                    _rageclawGUID = cr->GetGUID();
                    LockRageclaw(cr);
                }
            }
        }

        void LockRageclaw(Creature* rageclaw)
        {
            // pointer check not needed
            me->SetFacingToObject(rageclaw);
            rageclaw->SetFacingToObject(me);

            DoCast(rageclaw, SPELL_LEFT_CHAIN, true);
            DoCast(rageclaw, SPELL_RIGHT_CHAIN, true);
        }

        void UnlockRageclaw(Unit* /*who*/, Creature* rageclaw)
        {
            // pointer check not needed
            DoCast(rageclaw, SPELL_FREE_RAGECLAW, true);
            _rageclawGUID.Clear();
            me->DespawnOrUnsummon(1);
        }

        void SpellHit(Unit* caster, const SpellInfo* spell) override
        {
            if (spell->Id == SPELL_UNLOCK_SHACKLE)
            {
                Player* player = caster->ToPlayer();

                if (Creature* rageclaw = ObjectAccessor::GetCreature(*me, _rageclawGUID))
                {
                    if (Group* group = player->GetGroup())
                    {
                        group->DoForAllMembers([this, player, rageclaw](Player* member)
                        {
                            if (member->IsAtGroupRewardDistance(player))
                            {
                                member->KilledMonster(rageclaw->GetCreatureTemplate(), _rageclawGUID);
                            }
                        });
                    }
                    else
                    {
                        player->KilledMonster(rageclaw->GetCreatureTemplate(), _rageclawGUID);
                    }

                    UnlockRageclaw(caster, rageclaw);
                    me->DespawnOrUnsummon();
                }
                else
                {
                    me->setDeathState(DeathState::JustDied);
                }
            }
        }

    private:
        ObjectGuid _rageclawGUID;
        uint32     timer;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_drakuru_shackles_groupquestsAI(creature);
    }
};

enum eFeedinDaGoolz
{
    NPC_DECAYING_GHOUL = 28565,
    GO_BOWL = 190656,
};

class npc_feedin_da_goolz_groupquests : public CreatureScript
{
public:
    npc_feedin_da_goolz_groupquests() : CreatureScript("npc_feedin_da_goolz") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_feedin_da_goolz_groupquestsAI(creature);
    }

    struct npc_feedin_da_goolz_groupquestsAI : public NullCreatureAI
    {
        npc_feedin_da_goolz_groupquestsAI(Creature* creature) : NullCreatureAI(creature) { findTimer = 1; checkTimer = 0; }

        uint32 findTimer;
        uint32 checkTimer;
        ObjectGuid ghoulFed;

        void UpdateAI(uint32 diff) override
        {
            if (findTimer)
            {
                findTimer += diff;
                if (findTimer >= 1000)
                {
                    if (Creature* ghoul = me->FindNearestCreature(NPC_DECAYING_GHOUL, 30.0f, true))
                    {
                        ghoul->SetReactState(REACT_DEFENSIVE);
                        float o = me->GetAngle(ghoul);
                        ghoul->GetMotionMaster()->MovePoint(1, me->GetPositionX() + 2 * cos(o), me->GetPositionY() + 2 * std::sin(o), me->GetPositionZ());
                        checkTimer = 1;
                        findTimer = 0;
                    }
                    else
                        findTimer = 1;
                }
                return;
            }

            if (checkTimer)
            {
                checkTimer += diff;
                if (checkTimer >= 1500)
                {
                    checkTimer = 1;
                    if (!ghoulFed)
                    {
                        if (Creature* ghoul = me->FindNearestCreature(NPC_DECAYING_GHOUL, 3.0f, true))
                        {
                            ghoulFed = ghoul->GetGUID();
                            ghoul->HandleEmoteCommand(EMOTE_ONESHOT_EAT);
                        }
                    }
                    else
                    {
                        if (GameObject* bowl = me->FindNearestGameObject(GO_BOWL, 10.0f))
                            bowl->Delete();

                        if (Creature* ghoul = ObjectAccessor::GetCreature(*me, ghoulFed))
                        {
                            ghoul->SetReactState(REACT_AGGRESSIVE);
                            ghoul->GetMotionMaster()->MoveTargetedHome();
                        }


                        if (Unit* owner = me->ToTempSummon()->GetSummonerUnit())
                        {
                            if (Player* player = owner->ToPlayer())
                            {
                                if (Group* group = player->GetGroup())
                                {
                                    group->DoForAllMembers([this, player](Player* member)
                                    {
                                        if (member->IsAtGroupRewardDistance(player))
                                        {
                                            member->KilledMonsterCredit(me->GetEntry());
                                        }
                                    });
                                }
                                else
                                {
                                    player->KilledMonsterCredit(me->GetEntry());
                                }
                            }
                        }

                        me->DespawnOrUnsummon(1);
                    }
                }
            }
        }
    };
};

enum ScourgeEnclosure
{
    QUEST_OUR_ONLY_HOPE                      = 12916,
    NPC_GYMER_DUMMY                          = 29928, // From quest template
    SPELL_GYMER_LOCK_EXPLOSION               = 55529
};

class go_scourge_enclosure_groupquests : public GameObjectScript
{
public:
    go_scourge_enclosure_groupquests() : GameObjectScript("go_scourge_enclosure") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton();

        if (player->GetQuestStatus(QUEST_OUR_ONLY_HOPE) == QUEST_STATUS_INCOMPLETE)
        {
            Creature* gymerDummy = go->FindNearestCreature(NPC_GYMER_DUMMY, 20.0f);
            if (gymerDummy)
            {
                gymerDummy->CastSpell(gymerDummy, SPELL_GYMER_LOCK_EXPLOSION, true);
                gymerDummy->DespawnOrUnsummon();
            }

            if (Group* group = player->GetGroup())
            {
                group->DoForAllMembers([this, player, gymerDummy](Player* member)
                {
                    if (member->IsAtGroupRewardDistance(player))
                    {
                        member->KilledMonsterCredit(gymerDummy->GetEntry(), gymerDummy->GetGUID());
                    }
                });
            }
            else
            {
                player->KilledMonsterCredit(gymerDummy->GetEntry(), gymerDummy->GetGUID());
            }
        }
        return true;
    }
};

void AddSC_zone_zuldrak_groupquests()
{
    new npc_drakuru_shackles_groupquests();
    new npc_feedin_da_goolz_groupquests();
    new go_scourge_enclosure_groupquests();
}
