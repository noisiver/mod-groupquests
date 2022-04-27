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

            if (player->GetQuestStatus(QUEST_FINDING_THE_SURVIVORS) != QUEST_STATUS_INCOMPLETE)
                return false;

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
