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

/*
 * Scripts for spells with SPELLFAMILY_GENERIC spells used for quests.
 * Ordered alphabetically using questId and scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_q#questID_".
 */

#include "GridNotifiers.h"
#include "ScriptMgr.h"
#include "SpellScript.h"

enum eDrakuru
{
    QUEST_SUBJECT_TO_INTERPRETATION         = 11991,
    QUEST_MY_HEART_IS_IN_YOUR_HANDS         = 12802,

    NPC_DRAKURU                             = 28016,
};

class spell_image_of_drakuru_reagent_check_groupquests : public SpellScriptLoader
{
public:
    spell_image_of_drakuru_reagent_check_groupquests() : SpellScriptLoader("spell_image_of_drakuru_reagent_check") { }

    class spell_image_of_drakuru_reagent_check_groupquests_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_image_of_drakuru_reagent_check_groupquests_SpellScript);

        void HandleDummyEffect(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (!caster || !caster->ToPlayer())
                return;
            Player* player = caster->ToPlayer();

            float dist = player->GetDistance(3385, -1807, 114);
            if (dist < 40.0f)
            {
                caster->ToPlayer()->GroupEventHappens(QUEST_SUBJECT_TO_INTERPRETATION, caster);
                caster->CastSpell(caster, 47118, false);

                if (Group* group = player->GetGroup())
                {
                    group->DoForAllMembers([player](Player* member)
                    {
                        if (member != player)
                        {
                            if (member->IsAtGroupRewardDistance(player))
                            {
                                if (!member->HasAura(47118))
                                {
                                    member->AddAura(47118, member);
                                }
                            }
                        }
                    });
                }
                return;
            }

            dist = player->GetDistance(4244, -2025, 238);
            if (dist < 40.0f)
            {
                caster->CastSpell(caster, 47150, false);

                if (Group* group = player->GetGroup())
                {
                    group->DoForAllMembers([player](Player* member)
                    {
                        if (member != player)
                        {
                            if (member->IsAtGroupRewardDistance(player))
                            {
                                if (!member->HasAura(47118))
                                {
                                    member->AddAura(47118, member);
                                }
                            }
                        }
                    });
                }
                return;
            }

            dist = player->GetDistance(4524, -3472, 228);
            if (dist < 40.0f)
            {
                caster->ToPlayer()->GroupEventHappens(QUEST_MY_HEART_IS_IN_YOUR_HANDS, caster);
                caster->CastSpell(caster, 47317, false);

                if (Group* group = player->GetGroup())
                {
                    group->DoForAllMembers([player](Player* member)
                    {
                        if (member != player)
                        {
                            if (member->IsAtGroupRewardDistance(player))
                            {
                                if (!member->HasAura(47118))
                                {
                                    member->AddAura(47118, member);
                                }
                            }
                        }
                    });
                }
                return;
            }

            dist = player->GetDistance(4599, -4877, 48);
            if (dist < 40.0f)
            {
                caster->CastSpell(caster, 47406, false);

                if (Group* group = player->GetGroup())
                {
                    group->DoForAllMembers([player](Player* member)
                    {
                        if (member != player)
                        {
                            if (member->IsAtGroupRewardDistance(player))
                            {
                                if (!member->HasAura(47118))
                                {
                                    member->AddAura(47118, member);
                                }
                            }
                        }
                    });
                }
                return;
            }

            dist = player->GetDistance(-236, -614, 116);
            if (dist < 40.0f)
            {
                caster->CastSpell(caster, 50440, false);

                if (Group* group = player->GetGroup())
                {
                    group->DoForAllMembers([player](Player* member)
                    {
                        if (member != player)
                        {
                            if (member->IsAtGroupRewardDistance(player))
                            {
                                if (!member->HasAura(47118))
                                {
                                    member->AddAura(47118, member);
                                }
                            }
                        }
                    });
                }
                return;
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_image_of_drakuru_reagent_check_groupquests_SpellScript::HandleDummyEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_image_of_drakuru_reagent_check_groupquests_SpellScript();
    }
};

class spell_summon_dark_messenger : public SpellScript
{
    PrepareSpellScript(spell_summon_dark_messenger);

    void HandleEffect(SpellEffIndex /*effIndex*/)
    {
        if (Player* player = GetCaster()->ToPlayer())
        {
            if (Group* group = player->GetGroup())
            {
                group->DoForAllMembers([player](Player* member)
                {
                    if (member != player)
                    {
                        if (member->IsAtGroupRewardDistance(player))
                        {
                            member->KilledMonsterCredit(32314);
                        }
                    }
                });
            }
        }
    }

    void Register() override
    {
        OnEffectLaunch += SpellEffectFn(spell_summon_dark_messenger::HandleEffect, EFFECT_1, SPELL_EFFECT_KILL_CREDIT);
    }
};

enum Quest12659Data
{
    NPC_SCALPS_KC_BUNNY = 28622,
};

class spell_q12659_ahunaes_knife_groupquests : public SpellScriptLoader
{
public:
    spell_q12659_ahunaes_knife_groupquests() : SpellScriptLoader("spell_q12659_ahunaes_knife") { }

    class spell_q12659_ahunaes_knife_groupquests_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_q12659_ahunaes_knife_groupquests_SpellScript);

        bool Load() override
        {
            return GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Player* caster = GetCaster()->ToPlayer();
            if (Creature* target = GetHitCreature())
            {
                target->DespawnOrUnsummon();

                if (Group* group = caster->GetGroup())
                {
                    group->DoForAllMembers([caster](Player* member)
                    {
                        if (member->IsAtGroupRewardDistance(caster))
                        {
                            member->KilledMonsterCredit(NPC_SCALPS_KC_BUNNY);
                        }
                    });
                }
                else
                {
                    caster->KilledMonsterCredit(NPC_SCALPS_KC_BUNNY);
                }
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_q12659_ahunaes_knife_groupquests_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_q12659_ahunaes_knife_groupquests_SpellScript();
    }
};

void AddSC_quest_spell_scripts_groupquests()
{
    new spell_image_of_drakuru_reagent_check_groupquests();
    RegisterSpellScript(spell_summon_dark_messenger);
    new spell_q12659_ahunaes_knife_groupquests();
}
