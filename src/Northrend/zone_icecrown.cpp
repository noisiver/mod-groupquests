#include "Group.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"

#define NPC_CAPTURED_CRUSADER 30407

class spell_drop_off_captured_crusader_groupquests : public SpellScriptLoader
{
public:
    spell_drop_off_captured_crusader_groupquests() : SpellScriptLoader("spell_drop_off_captured_crusader") { }

    class spell_drop_off_captured_crusader_groupquests_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_drop_off_captured_crusader_groupquests_SpellScript);

        void HandleEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (Player* player = caster->ToCreature()->GetOwner()->ToPlayer())
                    if (Group* group = player->GetGroup())
                        for (GroupReference* groupRef = group->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                            if (Player* member = groupRef->GetSource())
                                if (member->GetDistance2d(player) < 200 && member != player)
                                    member->KilledMonsterCredit(NPC_CAPTURED_CRUSADER);
        }

        void Register() override
        {
            OnEffectLaunch += SpellEffectFn(spell_drop_off_captured_crusader_groupquests_SpellScript::HandleEffect, EFFECT_1, SPELL_EFFECT_KILL_CREDIT);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_drop_off_captured_crusader_groupquests_SpellScript();
    }
};

void AddSC_zone_icecrown_groupquests()
{
    new spell_drop_off_captured_crusader_groupquests();
}
