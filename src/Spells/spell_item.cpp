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
                if (Group* group = player->GetGroup())
                    for (GroupReference* groupRef = group->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                        if (Player* member = groupRef->GetSource())
                            if (member->GetDistance2d(player) < 200 && member != player)
                                if (member->HasQuest(3123) && member->GetQuestStatus(3123) == QUEST_STATUS_INCOMPLETE)
                                    member->AddItem(9594, 1);
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

void AddSC_item_spell_scripts_groupquests()
{
    new spell_item_muisek_vessel_groupquests();
}
