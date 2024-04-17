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

enum Enraged_Dpirits
{
    // QUESTS
    QUEST_ENRAGED_SPIRITS_FIRE_EARTH = 10458,
    QUEST_ENRAGED_SPIRITS_AIR = 10481,
    QUEST_ENRAGED_SPIRITS_WATER = 10480,

    // Totem
    ENTRY_TOTEM_OF_SPIRITS = 21071,
    RADIUS_TOTEM_OF_SPIRITS = 15,

    // SPIRITS
    NPC_ENRAGED_EARTH_SPIRIT = 21050,
    NPC_ENRAGED_FIRE_SPIRIT = 21061,
    NPC_ENRAGED_AIR_SPIRIT = 21060,
    NPC_ENRAGED_WATER_SPIRIT = 21059,

    // SOULS
    NPC_EARTHEN_SOUL = 21073,
    NPC_FIERY_SOUL = 21097,
    NPC_ENRAGED_AIRY_SOUL = 21116,
    NPC_ENRAGED_WATERY_SOUL = 21109, // wrong model

    // SPELL KILLCREDIT - not working!?! - using KilledMonsterCredit
    SPELL_EARTHEN_SOUL_CAPTURED_CREDIT = 36108,
    SPELL_FIERY_SOUL_CAPTURED_CREDIT = 36117,
    SPELL_AIRY_SOUL_CAPTURED_CREDIT = 36182,
    SPELL_WATERY_SOUL_CAPTURED_CREDIT = 36171,

    // KilledMonsterCredit Workaround
    NPC_CREDIT_FIRE = 21094,
    NPC_CREDIT_WATER = 21095,
    NPC_CREDIT_AIR = 21096,
    NPC_CREDIT_EARTH = 21092,

    // Captured Spell / Buff
    SPELL_SOUL_CAPTURED = 36115
};

class npc_enraged_spirit_groupquests : public CreatureScript
{
public:
    npc_enraged_spirit_groupquests() : CreatureScript("npc_enraged_spirit") {}

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_enraged_spirit_groupquestsAI(creature);
    }

    struct npc_enraged_spirit_groupquestsAI : public ScriptedAI
    {
        npc_enraged_spirit_groupquestsAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset() override { }

        void JustEngagedWith(Unit* /*who*/) override { }

        void JustDied(Unit* /*killer*/) override
        {
            // always spawn spirit on death
            // if totem around
            // move spirit to totem and cast kill count
            uint32 entry = 0;
            uint32 credit = 0;

            switch (me->GetEntry())
            {
            case NPC_ENRAGED_FIRE_SPIRIT:
                entry = NPC_FIERY_SOUL;
                //credit = SPELL_FIERY_SOUL_CAPTURED_CREDIT;
                credit = NPC_CREDIT_FIRE;
                break;
            case NPC_ENRAGED_EARTH_SPIRIT:
                entry = NPC_EARTHEN_SOUL;
                //credit = SPELL_EARTHEN_SOUL_CAPTURED_CREDIT;
                credit = NPC_CREDIT_EARTH;
                break;
            case NPC_ENRAGED_AIR_SPIRIT:
                entry = NPC_ENRAGED_AIRY_SOUL;
                //credit = SPELL_AIRY_SOUL_CAPTURED_CREDIT;
                credit = NPC_CREDIT_AIR;
                break;
            case NPC_ENRAGED_WATER_SPIRIT:
                entry = NPC_ENRAGED_WATERY_SOUL;
                //credit = SPELL_WATERY_SOUL_CAPTURED_CREDIT;
                credit = NPC_CREDIT_WATER;
                break;
            default:
                break;
            }

            // Spawn Soul on Kill ALWAYS!
            Creature* Summoned = nullptr;
            Unit* totemOspirits = nullptr;

            if (entry != 0)
                Summoned = DoSpawnCreature(entry, 0, 0, 1, 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 5000);

            // FIND TOTEM, PROCESS QUEST
            if (Summoned)
            {
                totemOspirits = me->FindNearestCreature(ENTRY_TOTEM_OF_SPIRITS, RADIUS_TOTEM_OF_SPIRITS);
                if (totemOspirits)
                {
                    Summoned->SetFaction(FACTION_FRIENDLY);
                    Summoned->GetMotionMaster()->MovePoint(0, totemOspirits->GetPositionX(), totemOspirits->GetPositionY(), Summoned->GetPositionZ());

                    if (Unit* owner = totemOspirits->GetOwner())
                    {
                        if (Player* player = owner->ToPlayer())
                        {
                            if (Group* group = player->GetGroup())
                            {
                                group->DoForAllMembers([player, credit](Player* member)
                                {
                                    if (member->IsAtGroupRewardDistance(player))
                                    {
                                        member->KilledMonsterCredit(credit);
                                    }
                                });
                            }
                            else
                            {
                                player->KilledMonsterCredit(credit);
                            }
                        }
                    }

                    DoCast(totemOspirits, SPELL_SOUL_CAPTURED);
                }
            }
        }
    };
};

void AddSC_zone_shadowmoon_valley_groupquests()
{
    new npc_enraged_spirit_groupquests();
}
