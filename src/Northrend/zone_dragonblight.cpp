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
#include "ScriptMgr.h"
#include "SpellScript.h"

enum TorturerLeCraft
{
    SPELL_HEMORRHAGE = 30478,
    SPELL_KIDNEY_SHOT = 30621,
    SPELL_HIGH_EXECUTORS_BRANDING_IRON = 48603,
    NPC_TORTURER_LECRAFT = 27394,
    EVENT_HEMORRHAGE = 1,
    EVENT_KIDNEY_SHOT = 2,
    SAY_AGGRO = 0
};

class npc_torturer_lecraft_groupquests : public CreatureScript
{
public:
    npc_torturer_lecraft_groupquests() : CreatureScript("npc_torturer_lecraft") {}

    struct npc_torturer_lecraft_groupquestsAI : public ScriptedAI
    {
        npc_torturer_lecraft_groupquestsAI(Creature* creature) : ScriptedAI(creature)
        {
            _playerGUID.Clear();
        }

        void Reset() override
        {
            _textCounter = 1;
            _playerGUID.Clear();
        }

        void JustEngagedWith(Unit* who) override
        {
            _events.ScheduleEvent(EVENT_HEMORRHAGE, urand(5000, 8000));
            _events.ScheduleEvent(EVENT_KIDNEY_SHOT, urand(12000, 15000));

            if (Player* player = who->ToPlayer())
                Talk(SAY_AGGRO, player);
        }

        void SpellHit(Unit* caster, const SpellInfo* spell) override
        {
            if (spell->Id != SPELL_HIGH_EXECUTORS_BRANDING_IRON)
                return;

            if (Player* player = caster->ToPlayer())
            {
                if (_textCounter == 1)
                    _playerGUID = player->GetGUID();

                if (_playerGUID != player->GetGUID())
                    return;

                Talk(_textCounter, player);

                if (_textCounter == 5)
                {
                    if (Group* group = player->GetGroup())
                    {
                        group->DoForAllMembers([player](Player* member)
                        {
                            if (member->IsAtGroupRewardDistance(player))
                            {
                                member->KilledMonsterCredit(NPC_TORTURER_LECRAFT);
                            }
                        });
                    }
                    else
                    {
                        player->KilledMonsterCredit(NPC_TORTURER_LECRAFT);
                    }
                }

                ++_textCounter;

                if (_textCounter == 13)
                    _textCounter = 6;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_HEMORRHAGE:
                    DoCastVictim(SPELL_HEMORRHAGE);
                    _events.ScheduleEvent(EVENT_HEMORRHAGE, urand(12000, 168000));
                    break;
                case EVENT_KIDNEY_SHOT:
                    DoCastVictim(SPELL_KIDNEY_SHOT);
                    _events.ScheduleEvent(EVENT_KIDNEY_SHOT, urand(20000, 26000));
                    break;
                default:
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }

    private:
        EventMap   _events;
        uint8      _textCounter;
        ObjectGuid _playerGUID;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_torturer_lecraft_groupquestsAI(creature);
    }
};

void AddSC_zone_dragonblight_groupquests()
{
    new npc_torturer_lecraft_groupquests();
}
