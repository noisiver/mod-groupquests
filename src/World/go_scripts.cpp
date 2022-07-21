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

#include "GameObjectAI.h"
#include "Group.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"

enum JotunheimCage
{
    NPC_EBON_BLADE_PRISONER_HUMAN   = 30186,
    NPC_EBON_BLADE_PRISONER_NE      = 30194,
    NPC_EBON_BLADE_PRISONER_TROLL   = 30196,
    NPC_EBON_BLADE_PRISONER_ORC     = 30195,

    SPELL_SUMMON_BLADE_KNIGHT_H     = 56207,
    SPELL_SUMMON_BLADE_KNIGHT_NE    = 56209,
    SPELL_SUMMON_BLADE_KNIGHT_ORC   = 56212,
    SPELL_SUMMON_BLADE_KNIGHT_TROLL = 56214
};

class go_jotunheim_cage_groupquests : public GameObjectScript
{
public:
    go_jotunheim_cage_groupquests() : GameObjectScript("go_jotunheim_cage") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton();
        Creature* pPrisoner = go->FindNearestCreature(NPC_EBON_BLADE_PRISONER_HUMAN, 5.0f, true);
        if (!pPrisoner)
        {
            pPrisoner = go->FindNearestCreature(NPC_EBON_BLADE_PRISONER_TROLL, 5.0f, true);
            if (!pPrisoner)
            {
                pPrisoner = go->FindNearestCreature(NPC_EBON_BLADE_PRISONER_ORC, 5.0f, true);
                if (!pPrisoner)
                    pPrisoner = go->FindNearestCreature(NPC_EBON_BLADE_PRISONER_NE, 5.0f, true);
            }
        }
        if (!pPrisoner || !pPrisoner->IsAlive())
            return false;

        pPrisoner->DespawnOrUnsummon();

        if (Group* group = player->GetGroup())
            for (GroupReference* groupRef = group->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                if (Player* member = groupRef->GetSource())
                    if (member->GetDistance2d(player) < 200 && member != player)
                        member->KilledMonsterCredit(NPC_EBON_BLADE_PRISONER_HUMAN);

        player->KilledMonsterCredit(NPC_EBON_BLADE_PRISONER_HUMAN);

        switch (pPrisoner->GetEntry())
        {
            case NPC_EBON_BLADE_PRISONER_HUMAN:
                player->CastSpell(player, SPELL_SUMMON_BLADE_KNIGHT_H, true);
                break;
            case NPC_EBON_BLADE_PRISONER_NE:
                player->CastSpell(player, SPELL_SUMMON_BLADE_KNIGHT_NE, true);
                break;
            case NPC_EBON_BLADE_PRISONER_TROLL:
                player->CastSpell(player, SPELL_SUMMON_BLADE_KNIGHT_TROLL, true);
                break;
            case NPC_EBON_BLADE_PRISONER_ORC:
                player->CastSpell(player, SPELL_SUMMON_BLADE_KNIGHT_ORC, true);
                break;
        }
        return true;
    }
};

enum Tadpoles
{
    QUEST_OH_NOES_THE_TADPOLES = 11560,
    NPC_WINTERFIN_TADPOLE = 25201
};

class go_tadpole_cage_groupquests : public GameObjectScript
{
public:
    go_tadpole_cage_groupquests() : GameObjectScript("go_tadpole_cage") { }

    struct go_tadpole_cage_groupquestsAI : public GameObjectAI
    {
        go_tadpole_cage_groupquestsAI(GameObject* gameObject) : GameObjectAI(gameObject)
        {
            requireSummon = 2;
        }

        uint8 requireSummon;

        void SummonTadpoles()
        {
            requireSummon = 0;
            int8 count = urand(1, 3);
            for (int8 i = 0; i < count; ++i)
                me->SummonCreature(NPC_WINTERFIN_TADPOLE, me->GetPositionX() + cos(2 * M_PI * i / 3.0f) * 0.60f, me->GetPositionY() + std::sin(2 * M_PI * i / 3.0f) * 0.60f, me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
        }

        void OnStateChanged(uint32 state, Unit*  /*unit*/) override
        {
            if (requireSummon == 1 && state == GO_READY)
                requireSummon = 2;
        }

        void UpdateAI(uint32  /*diff*/) override
        {
            if (me->isSpawned() && requireSummon == 2)
                SummonTadpoles();
        }

        bool GossipHello(Player* player, bool  /*reportUse*/) override
        {
            if (requireSummon)
                return false;

            requireSummon = 1;

            std::list<Creature*> cList;
            GetCreatureListWithEntryInGrid(cList, me, NPC_WINTERFIN_TADPOLE, 5.0f);
            for (std::list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); ++itr)
            {
                (*itr)->DespawnOrUnsummon(urand(45000, 60000));
                (*itr)->GetMotionMaster()->MoveFollow(player, 1.0f, frand(0.0f, 2 * M_PI), MOTION_SLOT_CONTROLLED);

                if (Group* group = player->GetGroup())
                    for (GroupReference* groupRef = group->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                        if (Player* member = groupRef->GetSource())
                            if (member->GetDistance2d(player) < 200 && member != player)
                                    member->KilledMonsterCredit(NPC_WINTERFIN_TADPOLE);

                player->KilledMonsterCredit(NPC_WINTERFIN_TADPOLE);
            }

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_tadpole_cage_groupquestsAI(go);
    }
};

void AddSC_go_scripts_groupquests()
{
    new go_jotunheim_cage_groupquests();
    new go_tadpole_cage_groupquests();
}
