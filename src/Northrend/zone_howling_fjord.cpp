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

#include "PassiveAI.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptMgr.h"
#include "SpellInfo.h"
 
class npc_attracted_reef_bull_groupquests : public CreatureScript
{
public:
    npc_attracted_reef_bull_groupquests() : CreatureScript("npc_attracted_reef_bull") { }

    struct npc_attracted_reef_bull_groupquestsAI : public NullCreatureAI
    {
        npc_attracted_reef_bull_groupquestsAI(Creature* creature) : NullCreatureAI(creature)
        {
            me->SetDisableGravity(true);
            if (me->IsSummon())
                if (Unit* owner = me->ToTempSummon()->GetSummonerUnit())
                    me->GetMotionMaster()->MovePoint(0, *owner);
        }

        void MovementInform(uint32  /*type*/, uint32  /*id*/) override
        {
            if (Creature* cow = me->FindNearestCreature(24797, 5.0f, true))
            {
                me->CastSpell(me, 44460, true);
                me->DespawnOrUnsummon(10000);
                cow->CastSpell(cow, 44460, true);
                cow->DespawnOrUnsummon(10000);
                if (me->IsSummon())
                {
                    if (Unit* owner = me->ToTempSummon()->GetSummonerUnit())
                    {
                        if (Group* group = owner->ToPlayer()->GetGroup())
                        {
                            group->DoForAllMembers([owner](Player* member)
                            {
                                if (member->IsAtGroupRewardDistance(owner))
                                {
                                    member->CastSpell(member, 44463, true);
                                }
                            });
                        }
                        else
                        {
                            owner->CastSpell(owner, 44463, true);
                        }
                    }
                }
            }
        }

        void SpellHit(Unit* caster, SpellInfo const* spellInfo) override
        {
            if (caster && spellInfo->Id == 44454)
                me->GetMotionMaster()->MovePoint(0, *caster);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_attracted_reef_bull_groupquestsAI(creature);
    }
};

void AddSC_zone_howling_fjord_groupquests()
{
    new npc_attracted_reef_bull_groupquests();
}
