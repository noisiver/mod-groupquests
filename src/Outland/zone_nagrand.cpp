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
#include "ScriptedCreature.h"
#include "ScriptMgr.h"

enum CorkiData
{
    // first quest
    QUEST_HELP                                    = 9923,
    NPC_CORKI                                     = 18445,
    NPC_CORKI_CREDIT_1                            = 18369,
    GO_CORKIS_PRISON                              = 182349,
    CORKI_SAY_THANKS                              = 0,
    // 2nd quest
    QUEST_CORKIS_GONE_MISSING_AGAIN               = 9924,
    NPC_CORKI_2                                   = 20812,
    GO_CORKIS_PRISON_2                            = 182350,
    CORKI_SAY_PROMISE                             = 0,
    // 3rd quest
    QUEST_CHOWAR_THE_PILLAGER                     = 9955,
    NPC_CORKI_3                                   = 18369,
    NPC_CORKI_CREDIT_3                            = 18444,
    GO_CORKIS_PRISON_3                            = 182521,
    CORKI_SAY_LAST                                = 0
};

class go_corkis_prison_groupquests : public GameObjectScript
{
public:
    go_corkis_prison_groupquests() : GameObjectScript("go_corkis_prison") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->SetGoState(GO_STATE_READY);
        if (go->GetEntry() == GO_CORKIS_PRISON)
        {
            if (Creature* corki = go->FindNearestCreature(NPC_CORKI, 25, true))
            {
                corki->GetMotionMaster()->MovePoint(1, go->GetPositionX() + 5, go->GetPositionY(), go->GetPositionZ());
                if (player)
                    QuestCredit(player, NPC_CORKI_CREDIT_1);
            }
        }

        if (go->GetEntry() == GO_CORKIS_PRISON_2)
        {
            if (Creature* corki = go->FindNearestCreature(NPC_CORKI_2, 25, true))
            {
                corki->GetMotionMaster()->MovePoint(1, go->GetPositionX() - 5, go->GetPositionY(), go->GetPositionZ());
                if (player)
                    QuestCredit(player, NPC_CORKI_2);
            }
        }

        if (go->GetEntry() == GO_CORKIS_PRISON_3)
        {
            if (Creature* corki = go->FindNearestCreature(NPC_CORKI_3, 25, true))
            {
                corki->GetMotionMaster()->MovePoint(1, go->GetPositionX() + 4, go->GetPositionY(), go->GetPositionZ());
                if (player)
                    QuestCredit(player, NPC_CORKI_CREDIT_3);
            }
        }

        return true;
    }
    
private:
    void QuestCredit(Player* player, uint32 npcEntry)
    {
        if (Group* group = player->GetGroup())
        {
            for (GroupReference* groupRef = group->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                if (Player* member = groupRef->GetSource())
                {
                    if (member->IsInMap(player))
                    {
                        member->KilledMonsterCredit(npcEntry);
                    }
                }
            }
        }
        else
        {
            player->KilledMonsterCredit(npcEntry);
        }
    }
};

enum FindingTheSurvivorsData
{
    QUEST_FINDING_THE_SURVIVORS                     = 9948,
    NPC_MAGHAR_PRISONER                             = 18428,

    SAY_FREE                                        = 0,
};

class go_warmaul_prison_groupquests : public GameObjectScript
{
    public:
        go_warmaul_prison_groupquests() : GameObjectScript("go_warmaul_prison") { }

        bool OnGossipHello(Player* player, GameObject* go) override
        {
            go->UseDoorOrButton();

            if (Creature* prisoner = go->FindNearestCreature(NPC_MAGHAR_PRISONER, 5.0f))
            {
                if (Group* group = player->GetGroup())
                {
                    for (GroupReference* groupRef = group->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                    {
                        if (Player* member = groupRef->GetSource())
                        {
                            if (member->IsInMap(player))
                            {
                                member->KilledMonsterCredit(NPC_MAGHAR_PRISONER);
                            }
                        }
                    }
                }
                else
                {
                    player->KilledMonsterCredit(NPC_MAGHAR_PRISONER);
                }

                prisoner->AI()->Talk(SAY_FREE, player);
                prisoner->DespawnOrUnsummon(6000);
            }

            return true;
        }
};

void AddSC_zone_nagrand_groupquests()
{
    new go_corkis_prison_groupquests();
    new go_warmaul_prison_groupquests();
}
