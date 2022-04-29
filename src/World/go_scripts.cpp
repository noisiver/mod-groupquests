#include "GameObjectAI.h"
#include "Group.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"

enum Tadpoles
{
    QUEST_OH_NOES_THE_TADPOLES                    = 11560,
    NPC_WINTERFIN_TADPOLE                         = 25201
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
                    {
                        for (GroupReference* groupRef = group->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                        {
                            if (Player* member = groupRef->GetSource())
                            {
                                if (member->IsInMap(player))
                                {
                                    if (member->GetQuestStatus(QUEST_OH_NOES_THE_TADPOLES) == QUEST_STATUS_INCOMPLETE)
                                        member->KilledMonsterCredit(NPC_WINTERFIN_TADPOLE);
                                }
                            }
                        }
                    }
                    else
                    {
                        if (player->GetQuestStatus(QUEST_OH_NOES_THE_TADPOLES) == QUEST_STATUS_INCOMPLETE)
                            player->KilledMonsterCredit(NPC_WINTERFIN_TADPOLE);
                    }
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
    new go_tadpole_cage_groupquests();
}
