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
#include "ScriptMgr.h"

enum Nerubar
{
    NPC_WARSONG_PEON            = 25270,
    QUEST_TAKEN_BY_THE_SCOURGE  = 11611,
    SPELL_FREED_WARSONG_MAGE    = 45526,
    SPELL_FREED_WARSONG_SHAMAN  = 45527,
    SPELL_FREED_WARSONG_WARRIOR = 45514,
    SPELL_FREED_WARSONG_PEON    = 45532
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
                uint8 uiRand   = urand(0, 99);

                if (uiRand < 40)
                {
                    if (Group* group = player->GetGroup())
                    {
                        for (GroupReference* groupRef = group->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                        {
                            if (Player* member = groupRef->GetSource())
                            {
                                if (member->IsInMap(player) && member->GetQuestStatus(QUEST_TAKEN_BY_THE_SCOURGE) == QUEST_STATUS_INCOMPLETE)
                                {
                                    member->KilledMonsterCredit(NPC_WARSONG_PEON);
                                }
                            }
                        }

                        player->CastSpell(me, SPELL_FREED_WARSONG_PEON, true);
                    }
                    else
                    {
                        if (player->GetQuestStatus(QUEST_TAKEN_BY_THE_SCOURGE) == QUEST_STATUS_INCOMPLETE)
                        {
                            player->CastSpell(me, SPELL_FREED_WARSONG_PEON, true);
                            player->KilledMonsterCredit(NPC_WARSONG_PEON);
                        }
                    }
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

void AddSC_zone_borean_tundra_groupquests()
{
    new npc_nerubar_victim_groupquests();
}
