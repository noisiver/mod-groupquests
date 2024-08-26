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
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "CombatAI.h"
#include "PassiveAI.h"
#include "Vehicle.h"
#include "WaypointMgr.h"
#include "SpellScript.h"
#include "ScriptedGossip.h"

enum ReconnaissanceFlight
{
    NPC_PLANE = 28710, // Vic's Flying Machine
    NPC_PILOT = 28646,

    VIC_SAY_0 = 0,
    VIC_SAY_1 = 1,
    VIC_SAY_2 = 2,
    VIC_SAY_3 = 3,
    VIC_SAY_4 = 4,
    VIC_SAY_5 = 5,
    VIC_SAY_6 = 6,
    PLANE_EMOTE = 0,

    AURA_ENGINE = 52255, // Engine on Fire

    SPELL_LAND = 52226, // Land Flying Machine
    SPELL_CREDIT = 53328 // Land Flying Machine Credit
};

class npc_vics_flying_machine_groupquests : public CreatureScript
{
public:
    npc_vics_flying_machine_groupquests() : CreatureScript("npc_vics_flying_machine") { }

    struct npc_vics_flying_machine_groupquestsAI : public VehicleAI
    {
        npc_vics_flying_machine_groupquestsAI(Creature* creature) : VehicleAI(creature)
        {
            pointId = 0;
        }

        uint8 pointId;

        void PassengerBoarded(Unit* passenger, int8 /*seatId*/, bool apply) override
        {
            if (apply && passenger->GetTypeId() == TYPEID_PLAYER)
            {
                Movement::PointsArray pathPoints;
                pathPoints.push_back(G3D::Vector3(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()));

                WaypointPath const* i_path = sWaypointMgr->GetPath(NPC_PLANE);
                for (uint8 i = 0; i < i_path->size(); ++i)
                {
                    WaypointData const* node = i_path->at(i);
                    pathPoints.push_back(G3D::Vector3(node->x, node->y, node->z));
                }

                me->GetMotionMaster()->MoveSplinePath(&pathPoints);
            }
        }

        void MovementInform(uint32 type, uint32  /*id*/) override
        {
            if (type != ESCORT_MOTION_TYPE)
                return;

            if (Vehicle* veh = me->GetVehicleKit())
                if (Unit* pilot = veh->GetPassenger(0))
                    switch (pointId)
                    {
                    case 5:
                        pilot->ToCreature()->AI()->Talk(VIC_SAY_0);
                        break;
                    case 11:
                        pilot->ToCreature()->AI()->Talk(VIC_SAY_1);
                        break;
                    case 12:
                        pilot->ToCreature()->AI()->Talk(VIC_SAY_2);
                        break;
                    case 14:
                        pilot->ToCreature()->AI()->Talk(VIC_SAY_3);
                        break;
                    case 15:
                        pilot->ToCreature()->ToCreature()->AI()->Talk(VIC_SAY_4);
                        break;
                    case 17:
                        pilot->ToCreature()->AI()->Talk(VIC_SAY_5);
                        break;
                    case 21:
                        pilot->ToCreature()->AI()->Talk(VIC_SAY_6);
                        break;
                    case 25:
                        Talk(PLANE_EMOTE);
                        DoCast(AURA_ENGINE);
                        me->SetUnitFlag2(UNIT_FLAG2_FORCE_MOVEMENT);
                        break;
                    }
            pointId++;
        }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_LAND)
            {
                Unit* passenger = me->GetVehicleKit()->GetPassenger(1); // player should be on seat 1
                if (passenger && passenger->GetTypeId() == TYPEID_PLAYER)
                {                                  
                    if (Group* group = passenger->ToPlayer()->GetGroup())
                    {
                        group->DoForAllMembers([passenger](Player* member)
                        {
                            if (member->IsAtGroupRewardDistance(passenger->ToPlayer()))
                            {
                                member->CastSpell(member, SPELL_CREDIT, true);
                            }
                        });
                    }
                    else
                    {
                        passenger->CastSpell(passenger, SPELL_CREDIT, true);
                    }
                }

                me->DespawnOrUnsummon();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_vics_flying_machine_groupquestsAI(creature);
    }
};

enum KickWhatKick
{
    NPC_LUCKY_WILHELM = 28054,
    NPC_APPLE = 28053,
    NPC_DROSTAN = 28328,
    NPC_CRUNCHY = 28346,
    NPC_THICKBIRD = 28093,

    SPELL_HIT_APPLE = 51331,
    SPELL_MISS_APPLE = 51332,
    SPELL_MISS_BIRD_APPLE = 51366,
    SPELL_APPLE_FALL = 51371,
    SPELL_BIRD_FALL = 51369,

    EVENT_MISS = 0,
    EVENT_HIT = 1,
    EVENT_MISS_BIRD = 2,

    SAY_WILHELM_MISS = 0,
    SAY_WILHELM_HIT = 1,
    SAY_DROSTAN_REPLY_MISS = 0,
};

class spell_q12589_shoot_rjr_groupquests : public SpellScriptLoader
{
public:
    spell_q12589_shoot_rjr_groupquests() : SpellScriptLoader("spell_q12589_shoot_rjr") { }

    class spell_q12589_shoot_rjr : public SpellScript
    {
        PrepareSpellScript(spell_q12589_shoot_rjr);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_MISS_BIRD_APPLE, SPELL_BIRD_FALL, SPELL_MISS_APPLE, SPELL_HIT_APPLE, SPELL_APPLE_FALL });
        }

        SpellCastResult CheckCast()
        {
            if (Unit* target = GetExplTargetUnit())
                if (target->GetEntry() == NPC_LUCKY_WILHELM)
                    return SPELL_CAST_OK;

            SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_MUST_TARGET_WILHELM);
            return SPELL_FAILED_CUSTOM_ERROR;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            uint32 roll = urand(1, 100);

            uint8 ev;
            if (roll <= 50)
                ev = EVENT_MISS;
            else if (roll <= 83)
                ev = EVENT_HIT;
            else
                ev = EVENT_MISS_BIRD;

            Unit* shooter = GetCaster();
            Creature* wilhelm = GetHitUnit()->ToCreature();
            Creature* apple = shooter->FindNearestCreature(NPC_APPLE, 30);
            Creature* drostan = shooter->FindNearestCreature(NPC_DROSTAN, 30);

            if (!wilhelm || !apple || !drostan)
                return;

            switch (ev)
            {
            case EVENT_MISS_BIRD:
            {
                Creature* crunchy = shooter->FindNearestCreature(NPC_CRUNCHY, 30);
                Creature* bird = shooter->FindNearestCreature(NPC_THICKBIRD, 30);

                if (!bird || !crunchy)
                    ; // fall to EVENT_MISS
                else
                {
                    shooter->CastSpell(bird, SPELL_MISS_BIRD_APPLE);
                    bird->CastSpell(bird, SPELL_BIRD_FALL);
                    wilhelm->AI()->Talk(SAY_WILHELM_MISS);
                    drostan->AI()->Talk(SAY_DROSTAN_REPLY_MISS);

                    Unit::Kill(bird, bird);
                    crunchy->GetMotionMaster()->MovePoint(0, bird->GetPositionX(), bird->GetPositionY(),
                        bird->GetMapWaterOrGroundLevel(bird->GetPositionX(), bird->GetPositionY(), bird->GetPositionZ()));
                    /// @todo Make crunchy perform emote eat when he reaches the bird

                    break;
                }
                [[fallthrough]];
            }
            case EVENT_MISS:
            {
                shooter->CastSpell(wilhelm, SPELL_MISS_APPLE);
                wilhelm->AI()->Talk(SAY_WILHELM_MISS);
                drostan->AI()->Talk(SAY_DROSTAN_REPLY_MISS);
                break;
            }
            case EVENT_HIT:
            {
                shooter->CastSpell(apple, SPELL_HIT_APPLE);
                apple->CastSpell(apple, SPELL_APPLE_FALL);
                wilhelm->AI()->Talk(SAY_WILHELM_HIT);

                if (Player* player = shooter->ToPlayer())
                {
                    if (Group* group = player->GetGroup())
                    {
                        group->DoForAllMembers([player](Player* member)
                            {
                                if (member->IsAtGroupRewardDistance(player))
                                {
                                    member->KilledMonsterCredit(NPC_APPLE);
                                }
                            });
                    }
                    else
                    {
                        player->KilledMonsterCredit(NPC_APPLE);
                    }
                }

                //apple->DespawnOrUnsummon(); zomg!

                break;
            }
            }
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_q12589_shoot_rjr::CheckCast);
            OnEffectHitTarget += SpellEffectFn(spell_q12589_shoot_rjr::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_q12589_shoot_rjr();
    }
};

enum StillAtIt
{
    NPC_MANUS = 28566,
    NPC_WANTS_BANANAS = 28537,

    QUEST_STILL_AT_IT = 12644,
    GOSSIP_MANUS_MENU = 9713,

    SAY_MANUS_START = 0,
    SAY_MANUS_ORANGE = 1,
    SAY_MANUS_PAPAYA = 2,
    SAY_MANUS_BANANA = 3,
    SAY_MANUS_PRESSUE = 4,
    SAY_MANUS_HEAT = 5,
    SAY_MANUS_WELL_DONE = 6,
    SAY_MANUS_FAILED = 7,
    SAY_MANUS_END = 8,
};

class npc_still_at_it_trigger_groupquests : public CreatureScript
{
public:
    npc_still_at_it_trigger_groupquests() : CreatureScript("npc_still_at_it_trigger") { }

    CreatureAI* GetAI(Creature* pCreature) const override
    {
        return new npc_still_at_it_trigger_groupquestsAI(pCreature);
    }

    struct npc_still_at_it_trigger_groupquestsAI : public NullCreatureAI
    {
        bool running;
        bool success;
        ObjectGuid playerGUID;
        ObjectGuid thunderbrewGUID;
        int32 tensecstimer;
        int32 timer;
        uint8 stepcount;
        uint8 currentstep;
        uint8 expectedaction;
        uint8 playeraction;

        npc_still_at_it_trigger_groupquestsAI(Creature* pCreature) : NullCreatureAI(pCreature) {}

        Creature* GetManus() { return ObjectAccessor::GetCreature(*me, thunderbrewGUID); }

        void Reset() override
        {
            running = false;
            success = false;
            playerGUID.Clear();
            thunderbrewGUID.Clear();
            tensecstimer = 0;
            timer = 0;
            stepcount = 0;
            currentstep = 0;
            expectedaction = 0;
            playeraction = 0;
        }

        void DamageTaken(Unit*, uint32& damage, DamageEffectType, SpellSchoolMask) override
        {
            damage = 0;
        }

        void Start()
        {
            timer = 5000;
            running = true;
            stepcount = urand(5, 10);
            GetManus()->AI()->Talk(SAY_MANUS_START);
        }

        void CheckAction(uint8 a, ObjectGuid guid)
        {
            if (guid != playerGUID)
                return;

            if (a == expectedaction)
            {
                currentstep++;

                if (Creature* th = ObjectAccessor::GetCreature(*me, thunderbrewGUID))
                    th->HandleEmoteCommand(EMOTE_ONESHOT_CHEER_NO_SHEATHE);

                GetManus()->AI()->Talk(SAY_MANUS_WELL_DONE);

                if (currentstep >= stepcount)
                {
                    GetManus()->AI()->Talk(SAY_MANUS_WELL_DONE);
                    success = true;
                    timer = 3000;
                }
                else
                {
                    expectedaction = 0;
                    timer = 3000;
                }
            }
            else
            {
                GetManus()->AI()->Talk(SAY_MANUS_FAILED);
                Reset();
            }
        }

        void SpellHit(Unit* caster, SpellInfo const* spellInfo) override // for banana(51932), orange(51931), papaya(51933)
        {
            if (running)
            {
                uint8 a = 0;
                switch (spellInfo->Id)
                {
                case 51931:
                    a = 4;
                    break;
                case 51932:
                    a = 3;
                    break;
                case 51933:
                    a = 5;
                    break;
                }

                CheckAction(a, caster->GetGUID());
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (running)
            {
                if (timer)
                {
                    timer -= diff;
                    if (timer < 0)
                        timer = 0;
                }
                else if (success)
                {
                    GetManus()->AI()->Talk(SAY_MANUS_END);
                    Player* player = ObjectAccessor::FindConnectedPlayer(playerGUID);
                    if (Group* group = player->GetGroup())
                    {
                        group->DoForAllMembers([player](Player* member)
                        {
                            if (member->IsAtGroupRewardDistance(player))
                            {
                                if (member->GetQuestStatus(QUEST_STILL_AT_IT) == QUEST_STATUS_INCOMPLETE)
                                {
                                    member->AddItem(38688, 1);
                                }
                            }
                        });
                    }
                    else
                    {
                        me->SummonGameObject(190643, 5546.55f, 5768.0f, -78.03f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0);
                    }

                    Reset();
                }
                else if (expectedaction != 0) // didn't make it in 10 seconds
                {
                    GetManus()->AI()->Talk(SAY_MANUS_FAILED);
                    Reset();
                }
                else // it's time to rand next move
                {
                    expectedaction = urand(1, 5);
                    switch (expectedaction)
                    {
                    case 1:
                        GetManus()->AI()->Talk(SAY_MANUS_PRESSUE);
                        break;
                    case 2:
                        GetManus()->AI()->Talk(SAY_MANUS_HEAT);
                        break;
                    case 3:
                        GetManus()->AI()->Talk(SAY_MANUS_BANANA);
                        break;
                    case 4:
                        GetManus()->AI()->Talk(SAY_MANUS_ORANGE);
                        break;
                    case 5:
                        GetManus()->AI()->Talk(SAY_MANUS_PAPAYA);
                        break;
                    }
                    timer = 10000;
                }
            }
        }
    };
};

class npc_mcmanus_groupquests : public CreatureScript
{
public:
    npc_mcmanus_groupquests() : CreatureScript("npc_mcmanus") {}

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (!player)
            return true;

        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_STILL_AT_IT) == QUEST_STATUS_INCOMPLETE)
            AddGossipItemFor(player, GOSSIP_MANUS_MENU, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        SendGossipMenuFor(player, player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32  /*uiSender*/, uint32 uiAction) override
    {
        if (!player)
            return true;

        if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
        {
            Creature* trigger = creature->FindNearestCreature(NPC_WANTS_BANANAS, 20.0f, true);
            if (trigger && trigger->AI())
                if (!CAST_AI(npc_still_at_it_trigger_groupquests::npc_still_at_it_trigger_groupquestsAI, trigger->AI())->running)
                {
                    CAST_AI(npc_still_at_it_trigger_groupquests::npc_still_at_it_trigger_groupquestsAI, trigger->AI())->playerGUID = player->GetGUID();
                    CAST_AI(npc_still_at_it_trigger_groupquests::npc_still_at_it_trigger_groupquestsAI, trigger->AI())->thunderbrewGUID = creature->GetGUID();
                    CAST_AI(npc_still_at_it_trigger_groupquests::npc_still_at_it_trigger_groupquestsAI, trigger->AI())->Start();
                }
        }

        CloseGossipMenuFor(player);
        return true;
    }
};

class go_pressure_valve_groupquests : public GameObjectScript
{
public:
    go_pressure_valve_groupquests() : GameObjectScript("go_pressure_valve") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (!player)
            return true;

        Creature* trigger = go->FindNearestCreature(NPC_WANTS_BANANAS, 20.0f, true);
        if (trigger && trigger->AI())
            if (CAST_AI(npc_still_at_it_trigger_groupquests::npc_still_at_it_trigger_groupquestsAI, trigger->AI())->running)
                CAST_AI(npc_still_at_it_trigger_groupquests::npc_still_at_it_trigger_groupquestsAI, trigger->AI())->CheckAction(1, player->GetGUID());

        return false;
    }
};

class go_brazier_groupquests : public GameObjectScript
{
public:
    go_brazier_groupquests() : GameObjectScript("go_brazier") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (!player)
            return true;

        Creature* trigger = go->FindNearestCreature(NPC_WANTS_BANANAS, 20.0f, true);
        if (trigger && trigger->AI())
            if (CAST_AI(npc_still_at_it_trigger_groupquests::npc_still_at_it_trigger_groupquestsAI, trigger->AI())->running)
                CAST_AI(npc_still_at_it_trigger_groupquests::npc_still_at_it_trigger_groupquestsAI, trigger->AI())->CheckAction(2, player->GetGUID());

        return false;
    }
};

void AddSC_zone_sholazar_basin_groupquests()
{
    new npc_vics_flying_machine_groupquests();
    new spell_q12589_shoot_rjr_groupquests();
    new npc_still_at_it_trigger_groupquests();
    new npc_mcmanus_groupquests();
    new go_pressure_valve_groupquests();
    new go_brazier_groupquests();
}
