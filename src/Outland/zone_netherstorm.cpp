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
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"

enum MaxxAMillion
{
    QUEST_MARK_V_IS_ALIVE = 10191,
    GO_DRAENEI_MACHINE = 183771
};

class npc_maxx_a_million_escort_groupquests : public CreatureScript
{
public:
    npc_maxx_a_million_escort_groupquests() : CreatureScript("npc_maxx_a_million_escort") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_maxx_a_million_escort_groupquestsAI(creature);
    }

    struct npc_maxx_a_million_escort_groupquestsAI : public npc_escortAI
    {
        npc_maxx_a_million_escort_groupquestsAI(Creature* creature) : npc_escortAI(creature) { }

        bool bTake;
        uint32 uiTakeTimer;

        void Reset() override
        {
            bTake = false;
            uiTakeTimer = 3000;
        }

        void WaypointReached(uint32 waypointId) override
        {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            switch (waypointId)
            {
            case 7:
            case 17:
            case 29:
                //Find Object and "work"
                if (GetClosestGameObjectWithEntry(me, GO_DRAENEI_MACHINE, INTERACTION_DISTANCE))
                {
                    // take the GO -> animation
                    me->HandleEmoteCommand(EMOTE_STATE_LOOT);
                    SetEscortPaused(true);
                    bTake = true;
                }
                break;
            case 36: //return and quest_complete
                if (Group* group = player->GetGroup())
                {
                    group->DoForAllMembers([player](Player* member)
                    {
                        if (member->IsAtGroupRewardDistance(player))
                        {
                            member->CompleteQuest(QUEST_MARK_V_IS_ALIVE);
                        }
                    });
                }
                else
                {
                    player->CompleteQuest(QUEST_MARK_V_IS_ALIVE);
                }
                break;
            }
        }

        void JustDied(Unit* /*killer*/) override
        {
            if (Player* player = GetPlayerForEscort())
            {
                if (Group* group = player->GetGroup())
                {
                    group->DoForAllMembers([player](Player* member)
                    {
                        if (member->IsAtGroupRewardDistance(player))
                        {
                            member->FailQuest(QUEST_MARK_V_IS_ALIVE);
                        }
                    });
                }
                else
                {
                    player->FailQuest(QUEST_MARK_V_IS_ALIVE);
                }
            }
        }

        void UpdateAI(uint32 uiDiff) override
        {
            npc_escortAI::UpdateAI(uiDiff);

            if (bTake)
            {
                if (uiTakeTimer < uiDiff)
                {
                    me->HandleEmoteCommand(EMOTE_STATE_NONE);
                    if (GameObject* go = GetClosestGameObjectWithEntry(me, GO_DRAENEI_MACHINE, INTERACTION_DISTANCE))
                    {
                        SetEscortPaused(false);
                        bTake = false;
                        uiTakeTimer = 3000;
                        go->Delete();
                    }
                }
                else
                    uiTakeTimer -= uiDiff;
            }
            DoMeleeAttackIfReady();
        }
    };

    bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest) override
    {
        if (quest->GetQuestId() == QUEST_MARK_V_IS_ALIVE)
        {
            if (npc_maxx_a_million_escort_groupquestsAI* pEscortAI = CAST_AI(npc_maxx_a_million_escort_groupquests::npc_maxx_a_million_escort_groupquestsAI, creature->AI()))
            {
                creature->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
                pEscortAI->Start(false, false, player->GetGUID());
            }
        }
        return true;
    }
};

enum CommanderDawnforgeData
{
    SAY_COMMANDER_DAWNFORGE_1 = 0,
    SAY_COMMANDER_DAWNFORGE_2 = 1,
    SAY_COMMANDER_DAWNFORGE_3 = 2,
    SAY_COMMANDER_DAWNFORGE_4 = 3,
    SAY_COMMANDER_DAWNFORGE_5 = 4,

    SAY_ARCANIST_ARDONIS_1 = 0,
    SAY_ARCANIST_ARDONIS_2 = 1,

    SAY_PATHALEON_CULATOR_IMAGE_1 = 0,
    SAY_PATHALEON_CULATOR_IMAGE_2 = 1,
    SAY_PATHALEON_CULATOR_IMAGE_2_1 = 2,
    SAY_PATHALEON_CULATOR_IMAGE_2_2 = 3,

    QUEST_INFO_GATHERING = 10198,
    SPELL_SUNFURY_DISGUISE = 34603,
};

// Entries of Arcanist Ardonis, Commander Dawnforge, Pathaleon the Curators Image
const uint32 CreatureEntry[3] =
{
    19830,                                                // Ardonis
    19831,                                                // Dawnforge
    21504                                                 // Pathaleon
};

class npc_commander_dawnforge_groupquests : public CreatureScript
{
public:
    npc_commander_dawnforge_groupquests() : CreatureScript("npc_commander_dawnforge") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_commander_dawnforge_groupquestsAI(creature);
    }

    struct npc_commander_dawnforge_groupquestsAI : public ScriptedAI
    {
        npc_commander_dawnforge_groupquestsAI(Creature* creature) : ScriptedAI(creature) { }

        ObjectGuid PlayerGUID;
        ObjectGuid ardonisGUID;
        ObjectGuid pathaleonGUID;

        uint32 Phase;
        uint32 PhaseSubphase;
        uint32 Phase_Timer;
        bool isEvent;

        void Reset() override
        {
            PlayerGUID.Clear();
            ardonisGUID.Clear();
            pathaleonGUID.Clear();

            Phase = 1;
            PhaseSubphase = 0;
            Phase_Timer = 4000;
            isEvent = false;
        }

        void JustEngagedWith(Unit* /*who*/) override { }

        void JustSummoned(Creature* summoned) override
        {
            pathaleonGUID = summoned->GetGUID();
        }

        // Emote Ardonis and Pathaleon
        void Turn_to_Pathaleons_Image()
        {
            Creature* ardonis = ObjectAccessor::GetCreature(*me, ardonisGUID);
            Creature* pathaleon = ObjectAccessor::GetCreature(*me, pathaleonGUID);

            if (!ardonis || !pathaleon)
                return;

            // Turn Dawnforge
            me->SetFacingToObject(pathaleon);

            // Turn Ardonis
            ardonis->SetFacingToObject(pathaleon);

            //Set them to kneel
            me->SetStandState(UNIT_STAND_STATE_KNEEL);
            ardonis->SetStandState(UNIT_STAND_STATE_KNEEL);
        }

        //Set them back to each other
        void Turn_to_eachother()
        {
            if (Unit* ardonis = ObjectAccessor::GetUnit(*me, ardonisGUID))
            {
                // Turn Dawnforge
                me->SetFacingToObject(ardonis);

                // Turn Ardonis
                ardonis->SetFacingToObject(me);

                //Set state
                me->SetStandState(UNIT_STAND_STATE_STAND);
                ardonis->SetStandState(UNIT_STAND_STATE_STAND);
            }
        }

        bool CanStartEvent(Player* player)
        {
            if (!isEvent)
            {
                Creature* ardonis = me->FindNearestCreature(CreatureEntry[0], 10.0f);
                if (!ardonis)
                    return false;

                ardonisGUID = ardonis->GetGUID();
                PlayerGUID = player->GetGUID();

                isEvent = true;

                Turn_to_eachother();
                return true;
            }

            LOG_DEBUG("scripts.ai", "npc_commander_dawnforge event already in progress, need to wait.");
            return false;
        }

        void UpdateAI(uint32 diff) override
        {
            //Is event even running?
            if (!isEvent)
                return;

            //Phase timing
            if (Phase_Timer >= diff)
            {
                Phase_Timer -= diff;
                return;
            }

            Creature* ardonis = ObjectAccessor::GetCreature(*me, ardonisGUID);
            Creature* pathaleon = ObjectAccessor::GetCreature(*me, pathaleonGUID);
            Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);

            if (!ardonis || !player)
            {
                Reset();
                return;
            }

            if (Phase > 4 && !pathaleon)
            {
                Reset();
                return;
            }

            //Phase 1 Dawnforge say
            switch (Phase)
            {
            case 1:
                Talk(SAY_COMMANDER_DAWNFORGE_1);
                ++Phase;
                Phase_Timer = 16000;
                break;
                //Phase 2 Ardonis say
            case 2:
                ardonis->AI()->Talk(SAY_ARCANIST_ARDONIS_1);
                ++Phase;
                Phase_Timer = 16000;
                break;
                //Phase 3 Dawnforge say
            case 3:
                Talk(SAY_COMMANDER_DAWNFORGE_2);
                ++Phase;
                Phase_Timer = 16000;
                break;
                //Phase 4 Pathaleon spawns up to phase 9
            case 4:
                //spawn pathaleon's image
                me->SummonCreature(CreatureEntry[2], 2325.851563f, 2799.534668f, 133.084229f, 6.038996f, TEMPSUMMON_TIMED_DESPAWN, 90000);
                ++Phase;
                Phase_Timer = 500;
                break;
                //Phase 5 Pathaleon say
            case 5:
                pathaleon->AI()->Talk(SAY_PATHALEON_CULATOR_IMAGE_1);
                ++Phase;
                Phase_Timer = 6000;
                break;
                //Phase 6
            case 6:
                switch (PhaseSubphase)
                {
                    //Subphase 1: Turn Dawnforge and Ardonis
                case 0:
                    Turn_to_Pathaleons_Image();
                    ++PhaseSubphase;
                    Phase_Timer = 8000;
                    break;
                    //Subphase 2 Dawnforge say
                case 1:
                    Talk(SAY_COMMANDER_DAWNFORGE_3);
                    PhaseSubphase = 0;
                    ++Phase;
                    Phase_Timer = 8000;
                    break;
                }
                break;
                //Phase 7 Pathaleons say 3 Sentence, every sentence need a subphase
            case 7:
                switch (PhaseSubphase)
                {
                    //Subphase 1
                case 0:
                    pathaleon->AI()->Talk(SAY_PATHALEON_CULATOR_IMAGE_2);
                    ++PhaseSubphase;
                    Phase_Timer = 12000;
                    break;
                    //Subphase 2
                case 1:
                    pathaleon->AI()->Talk(SAY_PATHALEON_CULATOR_IMAGE_2_1);
                    ++PhaseSubphase;
                    Phase_Timer = 16000;
                    break;
                    //Subphase 3
                case 2:
                    pathaleon->AI()->Talk(SAY_PATHALEON_CULATOR_IMAGE_2_2);
                    PhaseSubphase = 0;
                    ++Phase;
                    Phase_Timer = 10000;
                    break;
                }
                break;
                //Phase 8 Dawnforge & Ardonis say
            case 8:
                Talk(SAY_COMMANDER_DAWNFORGE_4);
                ardonis->AI()->Talk(SAY_ARCANIST_ARDONIS_2);
                ++Phase;
                Phase_Timer = 4000;
                break;
                //Phase 9 Pathaleons Despawn, Reset Dawnforge & Ardonis angle
            case 9:
                Turn_to_eachother();
                //hide pathaleon, unit will despawn shortly
                pathaleon->SetVisible(false);
                PhaseSubphase = 0;
                ++Phase;
                Phase_Timer = 3000;
                break;
                //Phase 10 Dawnforge say
            case 10:
                Talk(SAY_COMMANDER_DAWNFORGE_5);

                if (Group* group = player->GetGroup())
                {
                    group->DoForAllMembers([player](Player* member)
                    {
                        if (member->IsAtGroupRewardDistance(player))
                        {
                            member->AreaExploredOrEventHappens(QUEST_INFO_GATHERING);
                        }
                    });
                }
                else
                {
                    player->AreaExploredOrEventHappens(QUEST_INFO_GATHERING);
                }

                Reset();
                break;
            }
        }
    };
};

class at_commander_dawnforge_groupquests : public AreaTriggerScript
{
public:
    at_commander_dawnforge_groupquests() : AreaTriggerScript("at_commander_dawnforge") { }

    bool OnTrigger(Player* player, const AreaTrigger* /*at*/) override
    {
        //if player lost aura or not have at all, we should not try start event.
        if (!player->HasAura(SPELL_SUNFURY_DISGUISE))
            return false;

        if (player->IsAlive() && player->GetQuestStatus(QUEST_INFO_GATHERING) == QUEST_STATUS_INCOMPLETE)
        {
            Creature* Dawnforge = player->FindNearestCreature(CreatureEntry[1], 30.0f);
            if (!Dawnforge)
                return false;

            if (CAST_AI(npc_commander_dawnforge_groupquests::npc_commander_dawnforge_groupquestsAI, Dawnforge->AI())->CanStartEvent(player))
                return true;
        }
        return false;
    }
};

void AddSC_zone_netherstorm_groupquests()
{
    new npc_maxx_a_million_escort_groupquests();
    new npc_commander_dawnforge_groupquests();
    new at_commander_dawnforge_groupquests();
}
