#include "Group.h"
#include "PassiveAI.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptMgr.h"
#include "SpellScript.h"

enum DrakuruShackles
{
    NPC_RAGECLAW               = 29686,
    QUEST_TROLLS_IS_GONE_CRAZY = 12861,
    SPELL_LEFT_CHAIN           = 59951,
    SPELL_RIGHT_CHAIN          = 59952,
    SPELL_UNLOCK_SHACKLE       = 55083,
    SPELL_FREE_RAGECLAW        = 55223
};

class npc_drakuru_shackles_groupquests : public CreatureScript
{
    public:
        npc_drakuru_shackles_groupquests() : CreatureScript("npc_drakuru_shackles") {}

        struct npc_drakuru_shackles_groupquestsAI : public NullCreatureAI
        {
            npc_drakuru_shackles_groupquestsAI(Creature* creature) : NullCreatureAI(creature)
            {
                _rageclawGUID.Clear();
                timer = 0;
            }

            void Reset() override
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }

            void UpdateAI(uint32 diff) override
            {
                timer += diff;
                if (timer >= 2000)
                {
                    timer = 0;
                    if (_rageclawGUID)
                        return;

                    if (Creature* cr = me->FindNearestCreature(NPC_RAGECLAW, 10.0f))
                    {
                        _rageclawGUID = cr->GetGUID();
                        LockRageclaw(cr);
                    }
                }
            }

            void LockRageclaw(Creature* rageclaw)
            {
                // pointer check not needed
                me->SetFacingToObject(rageclaw);
                rageclaw->SetFacingToObject(me);

                DoCast(rageclaw, SPELL_LEFT_CHAIN, true);
                DoCast(rageclaw, SPELL_RIGHT_CHAIN, true);
            }

            void UnlockRageclaw(Unit* /*who*/, Creature* rageclaw)
            {
                // pointer check not needed
                DoCast(rageclaw, SPELL_FREE_RAGECLAW, true);
                _rageclawGUID.Clear();
                me->DespawnOrUnsummon(1);
            }

            void SpellHit(Unit* caster, const SpellInfo* spell) override
            {
                if (spell->Id == SPELL_UNLOCK_SHACKLE)
                {
                    Player* player = caster->ToPlayer();

                    if (Creature* rageclaw = ObjectAccessor::GetCreature(*me, _rageclawGUID))
                    {
                        if (Group* group = player->GetGroup())
                        {
                            UnlockRageclaw(player, rageclaw);

                            for (GroupReference* groupRef = group->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                            {
                                if (Player* member = groupRef->GetSource())
                                {
                                    if (member->IsInMap(player) && member->GetQuestStatus(QUEST_TROLLS_IS_GONE_CRAZY) == QUEST_STATUS_INCOMPLETE)
                                    {
                                        member->KilledMonster(rageclaw->GetCreatureTemplate(), _rageclawGUID);
                                    }
                                }
                            }

                            me->DespawnOrUnsummon();
                        }
                        else
                        {
                            if (player->GetQuestStatus(QUEST_TROLLS_IS_GONE_CRAZY) == QUEST_STATUS_INCOMPLETE)
                            {
                                UnlockRageclaw(caster, rageclaw);
                                player->KilledMonster(rageclaw->GetCreatureTemplate(), _rageclawGUID);
                                me->DespawnOrUnsummon();
                            }
                        }
                    }
                    else
                    {
                        me->setDeathState(JUST_DIED);
                    }
                }
            }

            private:
                ObjectGuid _rageclawGUID;
                uint32     timer;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_drakuru_shackles_groupquestsAI(creature);
        }
};

void AddSC_zone_zuldrak_groupquests()
{
    new npc_drakuru_shackles_groupquests();
}
