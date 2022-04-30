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
    new go_warmaul_prison_groupquests();
}
