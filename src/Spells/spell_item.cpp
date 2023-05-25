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
 * Scripts for spells with SPELLFAMILY_GENERIC spells used by items.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_item_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"

class spell_item_muisek_vessel_groupquests : public SpellScriptLoader
{
public:
    spell_item_muisek_vessel_groupquests() : SpellScriptLoader("spell_item_muisek_vessel") { }

    class spell_item_muisek_vessel_groupquests_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_item_muisek_vessel_groupquests_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Creature* target = GetHitCreature())
                if (target->isDead())
                    target->DespawnOrUnsummon();

            if (Player* player = GetCaster()->ToPlayer())
            {
                if (Group* group = player->GetGroup())
                {
                    for (GroupReference* groupRef = group->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                    {
                        if (Player* member = groupRef->GetSource())
                        {
                            if (member->GetDistance2d(player) < 200 && member != player)
                            {
                                switch (GetHitCreature()->GetCreatureTemplate()->Entry)
                                {
                                case 5276: // Sprite Dragon
                                case 5278: // Sprite Darter
                                    if (member->GetQuestStatus(3125) == QUEST_STATUS_INCOMPLETE)
                                        member->AddItem(9596, 1);
                                    break;
                                case 5268: // Ironfur Bear
                                case 5286: // Longtooth Runner
                                    if (member->GetQuestStatus(3123) == QUEST_STATUS_INCOMPLETE)
                                        member->AddItem(9594, 1);
                                    break;
                                case 5300: // Frayfeather Hippogryph
                                case 5304: // Frayfeather Stagwing
                                case 5305: // Frayfeather Skystormer
                                case 5306: // Frayfeather Patriarch
                                    if (member->GetQuestStatus(3124) == QUEST_STATUS_INCOMPLETE)
                                        member->AddItem(9595, 1);
                                    break;
                                case 5357: // Land Walker
                                case 5358: // Cliff Giant
                                    if (member->GetQuestStatus(3127) == QUEST_STATUS_INCOMPLETE)
                                        member->AddItem(9597, 1);
                                    break;
                                case 7584: // Wandering Forest Walker
                                    if (member->GetQuestStatus(3126) == QUEST_STATUS_INCOMPLETE)
                                        member->AddItem(9593, 1);
                                    break;
                                default:
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_item_muisek_vessel_groupquests_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_item_muisek_vessel_groupquests_SpellScript();
    }
};

class spell_item_kilsorrow_banner_groupquests : public SpellScriptLoader
{
public:
    spell_item_kilsorrow_banner_groupquests() : SpellScriptLoader("spell_item_kilsorrow_banner") { }

    class spell_item_kilsorrow_banner_groupquests_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_item_kilsorrow_banner_groupquests_SpellScript);

        void OnSummon(SpellEffIndex /*effIndex*/)
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (Group* group = player->GetGroup())
                {
                    for (GroupReference* groupRef = group->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                    {
                        if (Player* member = groupRef->GetSource())
                        {
                            if (member->GetDistance2d(player) < 200 && member != player)
                            {
                                if (member->GetQuestStatus(9931) == QUEST_STATUS_INCOMPLETE)
                                    member->KilledMonsterCredit(18393);
                            }
                        }
                    }
                }
            }
        }

        void Register() override
        {
            OnEffectLaunch += SpellEffectFn(spell_item_kilsorrow_banner_groupquests_SpellScript::OnSummon, EFFECT_0, SPELL_EFFECT_SUMMON_OBJECT_WILD);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_item_kilsorrow_banner_groupquests_SpellScript();
    }
};

void AddSC_item_spell_scripts_groupquests()
{
    new spell_item_muisek_vessel_groupquests();
    new spell_item_kilsorrow_banner_groupquests();
}
