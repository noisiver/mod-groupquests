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
#include "CombatAI.h"
#include "Vehicle.h"
#include "WaypointMgr.h"

enum ReconnaissanceFlight
{
    NPC_PLANE = 28710, // Vic's Flying Machine
    NPC_PILOT = 28646,

    VIC_SAY_0 = 0,
    VIC_SAY_1 = 1,
    VIC_SAY_2 = 2,
    VIC_SAY_3 = 3,
    VIC_SAY_4 = 4,
    VIC_SAY_5 = 5,
    VIC_SAY_6 = 6,
    PLANE_EMOTE = 0,

    AURA_ENGINE = 52255, // Engine on Fire

    SPELL_LAND = 52226, // Land Flying Machine
    SPELL_CREDIT = 53328 // Land Flying Machine Credit
};

class npc_vics_flying_machine_groupquests : public CreatureScript
{
    public:
        npc_vics_flying_machine_groupquests() : CreatureScript("npc_vics_flying_machine") { }

        struct npc_vics_flying_machine_groupquestsAI : public VehicleAI
        {
            npc_vics_flying_machine_groupquestsAI(Creature* creature) : VehicleAI(creature)
            {
                pointId = 0;
            }

            uint8 pointId;

            void PassengerBoarded(Unit* passenger, int8 /*seatId*/, bool apply) override
            {
                if (apply && passenger->GetTypeId() == TYPEID_PLAYER)
                {
                    Movement::PointsArray pathPoints;
                    pathPoints.push_back(G3D::Vector3(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()));

                    WaypointPath const* i_path = sWaypointMgr->GetPath(NPC_PLANE);
                    for (uint8 i = 0; i < i_path->size(); ++i)
                    {
                        WaypointData const* node = i_path->at(i);
                        pathPoints.push_back(G3D::Vector3(node->x, node->y, node->z));
                    }

                    me->GetMotionMaster()->MoveSplinePath(&pathPoints);
                }
            }

            void MovementInform(uint32 type, uint32  /*id*/) override
            {
                if (type != ESCORT_MOTION_TYPE)
                    return;

                if (Vehicle* veh = me->GetVehicleKit())
                    if (Unit* pilot = veh->GetPassenger(0))
                        switch (pointId)
                        {
                        case 5:
                            pilot->ToCreature()->AI()->Talk(VIC_SAY_0);
                            break;
                        case 11:
                            pilot->ToCreature()->AI()->Talk(VIC_SAY_1);
                            break;
                        case 12:
                            pilot->ToCreature()->AI()->Talk(VIC_SAY_2);
                            break;
                        case 14:
                            pilot->ToCreature()->AI()->Talk(VIC_SAY_3);
                            break;
                        case 15:
                            pilot->ToCreature()->ToCreature()->AI()->Talk(VIC_SAY_4);
                            break;
                        case 17:
                            pilot->ToCreature()->AI()->Talk(VIC_SAY_5);
                            break;
                        case 21:
                            pilot->ToCreature()->AI()->Talk(VIC_SAY_6);
                            break;
                        case 25:
                            Talk(PLANE_EMOTE);
                            DoCast(AURA_ENGINE);
                            me->SetUnitFlag2(UNIT_FLAG2_FORCE_MOVEMENT);
                            break;
                        }
                pointId++;
            }

            void SpellHit(Unit* /*caster*/, SpellInfo const* spell) override
            {
                if (spell->Id == SPELL_LAND)
                {
                    Unit* passenger = me->GetVehicleKit()->GetPassenger(1); // player should be on seat 1
                    if (passenger && passenger->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (Group* group = passenger->ToPlayer()->GetGroup())
                        {
                            for (GroupReference* groupRef = group->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                            {
                                if (Player* member = groupRef->GetSource())
                                {
                                    if (member->IsInMap(passenger))
                                    {
                                        member->CastSpell(member, SPELL_CREDIT, true);
                                    }
                                }
                            }
                        }
                        else
                        {
                            passenger->CastSpell(passenger, SPELL_CREDIT, true);
                        }
                    }

                    me->DespawnOrUnsummon();
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_vics_flying_machine_groupquestsAI(creature);
        }
};

void AddSC_zone_sholazar_basin_groupquests()
{
    new npc_vics_flying_machine_groupquests();
}
