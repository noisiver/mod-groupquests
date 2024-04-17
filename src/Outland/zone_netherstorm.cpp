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

void AddSC_zone_netherstorm_groupquests()
{
    new npc_maxx_a_million_escort_groupquests();
}
