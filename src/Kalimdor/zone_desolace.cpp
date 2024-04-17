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
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "SpellScript.h"

enum DyingKodo
{
    SAY_SMEED_HOME = 0,

    QUEST_KODO = 5561,

    NPC_SMEED = 11596,
    NPC_AGED_KODO = 4700,
    NPC_DYING_KODO = 4701,
    NPC_ANCIENT_KODO = 4702,
    NPC_TAMED_KODO = 11627,

    SPELL_KODO_KOMBO_ITEM = 18153,
    SPELL_KODO_KOMBO_PLAYER_BUFF = 18172,
    SPELL_KODO_KOMBO_DESPAWN_BUFF = 18377,
    SPELL_KODO_KOMBO_GOSSIP = 18362
};

class npc_aged_dying_ancient_kodo_groupquests : public CreatureScript
{
public:
    npc_aged_dying_ancient_kodo_groupquests() : CreatureScript("npc_aged_dying_ancient_kodo") {}

    struct npc_aged_dying_ancient_kodo_groupquestsAI : public ScriptedAI
    {
        npc_aged_dying_ancient_kodo_groupquestsAI(Creature* creature) : ScriptedAI(creature) {}

        void JustRespawned() override
        {
            me->UpdateEntry(RAND(NPC_AGED_KODO, NPC_DYING_KODO, NPC_ANCIENT_KODO), nullptr, false);
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (who->GetEntry() == NPC_SMEED && me->IsWithinDistInMap(who, 10.0f) && !me->HasAura(SPELL_KODO_KOMBO_GOSSIP))
            {
                me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MoveIdle();

                DoCast(me, SPELL_KODO_KOMBO_GOSSIP, true);
                if (Creature* smeed = who->ToCreature())
                    smeed->AI()->Talk(SAY_SMEED_HOME);
            }
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_KODO_KOMBO_ITEM)
            {
                if (!(caster->HasAura(SPELL_KODO_KOMBO_PLAYER_BUFF) || me->HasAura(SPELL_KODO_KOMBO_DESPAWN_BUFF)) && (me->GetEntry() == NPC_AGED_KODO || me->GetEntry() == NPC_DYING_KODO || me->GetEntry() == NPC_ANCIENT_KODO))
                {
                    me->UpdateEntry(NPC_TAMED_KODO, nullptr, false);
                    EnterEvadeMode();
                    me->GetMotionMaster()->MoveFollow(caster, PET_FOLLOW_DIST, me->GetFollowAngle());

                    caster->CastSpell(caster, SPELL_KODO_KOMBO_PLAYER_BUFF, true);
                    DoCast(me, SPELL_KODO_KOMBO_DESPAWN_BUFF, true);
                }
            }
            else if (spell->Id == SPELL_KODO_KOMBO_GOSSIP)
            {
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                me->DespawnOrUnsummon(60000);
            }
        }
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (player->HasAura(SPELL_KODO_KOMBO_PLAYER_BUFF) && creature->HasAura(SPELL_KODO_KOMBO_DESPAWN_BUFF))
        {
            if (Group* group = player->GetGroup())
            {
                group->DoForAllMembers([player, creature](Player* member)
                {
                    if (member->IsAtGroupRewardDistance(player))
                    {
                        member->TalkedToCreature(creature->GetEntry(), ObjectGuid::Empty);
                    }
                });
            }
            else
            {
                player->TalkedToCreature(creature->GetEntry(), ObjectGuid::Empty);
            }

            player->RemoveAurasDueToSpell(SPELL_KODO_KOMBO_PLAYER_BUFF);
        }

        SendGossipMenuFor(player, player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_aged_dying_ancient_kodo_groupquestsAI(creature);
    }
};

void AddSC_zone_desolace_groupquests()
{
    new npc_aged_dying_ancient_kodo_groupquests();
}
