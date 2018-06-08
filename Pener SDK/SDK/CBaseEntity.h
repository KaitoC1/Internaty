#pragma once

#include "../UTILS/offsets.h"
#include "../UTILS/interfaces.h"
#include "../SDK/ModelInfo.h"
#include "../UTILS/qangle.h"
#include "../UTILS/NetvarHookManager.h"
#include "AnimLayer.h"
#include "RecvData.h"

namespace SDK
{
	class CBaseAnimState;
	class Collideable;

	struct studiohdr_t;
	struct model_t;

	enum Activity
	{
		ACT_RESET,
		ACT_IDLE,
		ACT_TRANSITION,
		ACT_COVER,
		ACT_COVER_MED,
		ACT_COVER_LOW,
		ACT_WALK,
		ACT_WALK_AIM,
		ACT_WALK_CROUCH,
		ACT_WALK_CROUCH_AIM,
		ACT_RUN,
		ACT_RUN_AIM,
		ACT_RUN_CROUCH,
		ACT_RUN_CROUCH_AIM,
		ACT_RUN_PROTECTED,
		ACT_SCRIPT_CUSTOM_MOVE,
		ACT_RANGE_ATTACK1,
		ACT_RANGE_ATTACK2,
		ACT_RANGE_ATTACK1_LOW,
		ACT_RANGE_ATTACK2_LOW,
		ACT_DIESIMPLE,
		ACT_DIEBACKWARD,
		ACT_DIEFORWARD,
		ACT_DIEVIOLENT,
		ACT_DIERAGDOLL,
		ACT_FLY,
		ACT_HOVER,
		ACT_GLIDE,
		ACT_SWIM,
		ACT_JUMP,
		ACT_HOP,
		ACT_LEAP,
		ACT_LAND,
		ACT_CLIMB_UP,
		ACT_CLIMB_DOWN,
		ACT_CLIMB_DISMOUNT,
		ACT_SHIPLADDER_UP,
		ACT_SHIPLADDER_DOWN,
		ACT_STRAFE_LEFT,
		ACT_STRAFE_RIGHT,
		ACT_ROLL_LEFT,
		ACT_ROLL_RIGHT,
		ACT_TURN_LEFT,
		ACT_TURN_RIGHT,
		ACT_CROUCH,
		ACT_CROUCHIDLE,
		ACT_STAND,
		ACT_USE,
		ACT_ALIEN_BURROW_IDLE,
		ACT_ALIEN_BURROW_OUT,
		ACT_SIGNAL1,
		ACT_SIGNAL2,
		ACT_SIGNAL3,
		ACT_SIGNAL_ADVANCE,
		ACT_SIGNAL_FORWARD,
		ACT_SIGNAL_GROUP,
		ACT_SIGNAL_HALT,
		ACT_SIGNAL_LEFT,
		ACT_SIGNAL_RIGHT,
		ACT_SIGNAL_TAKECOVER,
		ACT_LOOKBACK_RIGHT,
		ACT_LOOKBACK_LEFT,
		ACT_COWER,
		ACT_SMALL_FLINCH,
		ACT_BIG_FLINCH,
		ACT_MELEE_ATTACK1,
		ACT_MELEE_ATTACK2,
		ACT_RELOAD,
		ACT_RELOAD_START,
		ACT_RELOAD_FINISH,
		ACT_RELOAD_LOW,
		ACT_ARM,
		ACT_DISARM,
		ACT_DROP_WEAPON,
		ACT_DROP_WEAPON_SHOTGUN,
		ACT_PICKUP_GROUND,
		ACT_PICKUP_RACK,
		ACT_IDLE_ANGRY,
		ACT_IDLE_RELAXED,
		ACT_IDLE_STIMULATED,
		ACT_IDLE_AGITATED,
		ACT_IDLE_STEALTH,
		ACT_IDLE_HURT,
		ACT_WALK_RELAXED,
		ACT_WALK_STIMULATED,
		ACT_WALK_AGITATED,
		ACT_WALK_STEALTH,
		ACT_RUN_RELAXED,
		ACT_RUN_STIMULATED,
		ACT_RUN_AGITATED,
		ACT_RUN_STEALTH,
		ACT_IDLE_AIM_RELAXED,
		ACT_IDLE_AIM_STIMULATED,
		ACT_IDLE_AIM_AGITATED,
		ACT_IDLE_AIM_STEALTH,
		ACT_WALK_AIM_RELAXED,
		ACT_WALK_AIM_STIMULATED,
		ACT_WALK_AIM_AGITATED,
		ACT_WALK_AIM_STEALTH,
		ACT_RUN_AIM_RELAXED,
		ACT_RUN_AIM_STIMULATED,
		ACT_RUN_AIM_AGITATED,
		ACT_RUN_AIM_STEALTH,
		ACT_CROUCHIDLE_STIMULATED,
		ACT_CROUCHIDLE_AIM_STIMULATED,
		ACT_CROUCHIDLE_AGITATED,
		ACT_WALK_HURT,
		ACT_RUN_HURT,
		ACT_SPECIAL_ATTACK1,
		ACT_SPECIAL_ATTACK2,
		ACT_COMBAT_IDLE,
		ACT_WALK_SCARED,
		ACT_RUN_SCARED,
		ACT_VICTORY_DANCE,
		ACT_DIE_HEADSHOT,
		ACT_DIE_CHESTSHOT,
		ACT_DIE_GUTSHOT,
		ACT_DIE_BACKSHOT,
		ACT_FLINCH_HEAD,
		ACT_FLINCH_CHEST,
		ACT_FLINCH_STOMACH,
		ACT_FLINCH_LEFTARM,
		ACT_FLINCH_RIGHTARM,
		ACT_FLINCH_LEFTLEG,
		ACT_FLINCH_RIGHTLEG,
		ACT_FLINCH_PHYSICS,
		ACT_FLINCH_HEAD_BACK,
		ACT_FLINCH_HEAD_LEFT,
		ACT_FLINCH_HEAD_RIGHT,
		ACT_FLINCH_CHEST_BACK,
		ACT_FLINCH_STOMACH_BACK,
		ACT_FLINCH_CROUCH_FRONT,
		ACT_FLINCH_CROUCH_BACK,
		ACT_FLINCH_CROUCH_LEFT,
		ACT_FLINCH_CROUCH_RIGHT,
		ACT_IDLE_ON_FIRE,
		ACT_WALK_ON_FIRE,
		ACT_RUN_ON_FIRE,
		ACT_RAPPEL_LOOP,
		ACT_180_LEFT,
		ACT_180_RIGHT,
		ACT_90_LEFT,
		ACT_90_RIGHT,
		ACT_STEP_LEFT,
		ACT_STEP_RIGHT,
		ACT_STEP_BACK,
		ACT_STEP_FORE,
		ACT_GESTURE_RANGE_ATTACK1,
		ACT_GESTURE_RANGE_ATTACK2,
		ACT_GESTURE_MELEE_ATTACK1,
		ACT_GESTURE_MELEE_ATTACK2,
		ACT_GESTURE_RANGE_ATTACK1_LOW,
		ACT_GESTURE_RANGE_ATTACK2_LOW,
		ACT_MELEE_ATTACK_SWING_GESTURE,
		ACT_GESTURE_SMALL_FLINCH,
		ACT_GESTURE_BIG_FLINCH,
		ACT_GESTURE_FLINCH_BLAST,
		ACT_GESTURE_FLINCH_BLAST_SHOTGUN,
		ACT_GESTURE_FLINCH_BLAST_DAMAGED,
		ACT_GESTURE_FLINCH_BLAST_DAMAGED_SHOTGUN,
		ACT_GESTURE_FLINCH_HEAD,
		ACT_GESTURE_FLINCH_CHEST,
		ACT_GESTURE_FLINCH_STOMACH,
		ACT_GESTURE_FLINCH_LEFTARM,
		ACT_GESTURE_FLINCH_RIGHTARM,
		ACT_GESTURE_FLINCH_LEFTLEG,
		ACT_GESTURE_FLINCH_RIGHTLEG,
		ACT_GESTURE_TURN_LEFT,
		ACT_GESTURE_TURN_RIGHT,
		ACT_GESTURE_TURN_LEFT45,
		ACT_GESTURE_TURN_RIGHT45,
		ACT_GESTURE_TURN_LEFT90,
		ACT_GESTURE_TURN_RIGHT90,
		ACT_GESTURE_TURN_LEFT45_FLAT,
		ACT_GESTURE_TURN_RIGHT45_FLAT,
		ACT_GESTURE_TURN_LEFT90_FLAT,
		ACT_GESTURE_TURN_RIGHT90_FLAT,
		ACT_BARNACLE_HIT,
		ACT_BARNACLE_PULL,
		ACT_BARNACLE_CHOMP,
		ACT_BARNACLE_CHEW,
		ACT_DO_NOT_DISTURB,
		ACT_SPECIFIC_SEQUENCE,
		ACT_VM_DRAW,
		ACT_VM_HOLSTER,
		ACT_VM_IDLE,
		ACT_VM_FIDGET,
		ACT_VM_PULLBACK,
		ACT_VM_PULLBACK_HIGH,
		ACT_VM_PULLBACK_LOW,
		ACT_VM_THROW,
		ACT_VM_PULLPIN,
		ACT_VM_PRIMARYATTACK,
		ACT_VM_SECONDARYATTACK,
		ACT_VM_RELOAD,
		ACT_VM_DRYFIRE,
		ACT_VM_HITLEFT,
		ACT_VM_HITLEFT2,
		ACT_VM_HITRIGHT,
		ACT_VM_HITRIGHT2,
		ACT_VM_HITCENTER,
		ACT_VM_HITCENTER2,
		ACT_VM_MISSLEFT,
		ACT_VM_MISSLEFT2,
		ACT_VM_MISSRIGHT,
		ACT_VM_MISSRIGHT2,
		ACT_VM_MISSCENTER,
		ACT_VM_MISSCENTER2,
		ACT_VM_HAULBACK,
		ACT_VM_SWINGHARD,
		ACT_VM_SWINGMISS,
		ACT_VM_SWINGHIT,
		ACT_VM_IDLE_TO_LOWERED,
		ACT_VM_IDLE_LOWERED,
		ACT_VM_LOWERED_TO_IDLE,
		ACT_VM_RECOIL1,
		ACT_VM_RECOIL2,
		ACT_VM_RECOIL3,
		ACT_VM_PICKUP,
		ACT_VM_RELEASE,
		ACT_VM_ATTACH_SILENCER,
		ACT_VM_DETACH_SILENCER,
		ACT_VM_EMPTY_FIRE,
		ACT_VM_EMPTY_RELOAD,
		ACT_VM_EMPTY_DRAW,
		ACT_VM_EMPTY_IDLE,
		ACT_SLAM_STICKWALL_IDLE,
		ACT_SLAM_STICKWALL_ND_IDLE,
		ACT_SLAM_STICKWALL_ATTACH,
		ACT_SLAM_STICKWALL_ATTACH2,
		ACT_SLAM_STICKWALL_ND_ATTACH,
		ACT_SLAM_STICKWALL_ND_ATTACH2,
		ACT_SLAM_STICKWALL_DETONATE,
		ACT_SLAM_STICKWALL_DETONATOR_HOLSTER,
		ACT_SLAM_STICKWALL_DRAW,
		ACT_SLAM_STICKWALL_ND_DRAW,
		ACT_SLAM_STICKWALL_TO_THROW,
		ACT_SLAM_STICKWALL_TO_THROW_ND,
		ACT_SLAM_STICKWALL_TO_TRIPMINE_ND,
		ACT_SLAM_THROW_IDLE,
		ACT_SLAM_THROW_ND_IDLE,
		ACT_SLAM_THROW_THROW,
		ACT_SLAM_THROW_THROW2,
		ACT_SLAM_THROW_THROW_ND,
		ACT_SLAM_THROW_THROW_ND2,
		ACT_SLAM_THROW_DRAW,
		ACT_SLAM_THROW_ND_DRAW,
		ACT_SLAM_THROW_TO_STICKWALL,
		ACT_SLAM_THROW_TO_STICKWALL_ND,
		ACT_SLAM_THROW_DETONATE,
		ACT_SLAM_THROW_DETONATOR_HOLSTER,
		ACT_SLAM_THROW_TO_TRIPMINE_ND,
		ACT_SLAM_TRIPMINE_IDLE,
		ACT_SLAM_TRIPMINE_DRAW,
		ACT_SLAM_TRIPMINE_ATTACH,
		ACT_SLAM_TRIPMINE_ATTACH2,
		ACT_SLAM_TRIPMINE_TO_STICKWALL_ND,
		ACT_SLAM_TRIPMINE_TO_THROW_ND,
		ACT_SLAM_DETONATOR_IDLE,
		ACT_SLAM_DETONATOR_DRAW,
		ACT_SLAM_DETONATOR_DETONATE,
		ACT_SLAM_DETONATOR_HOLSTER,
		ACT_SLAM_DETONATOR_STICKWALL_DRAW,
		ACT_SLAM_DETONATOR_THROW_DRAW,
		ACT_SHOTGUN_RELOAD_START,
		ACT_SHOTGUN_RELOAD_FINISH,
		ACT_SHOTGUN_PUMP,
		ACT_SMG2_IDLE2,
		ACT_SMG2_FIRE2,
		ACT_SMG2_DRAW2,
		ACT_SMG2_RELOAD2,
		ACT_SMG2_DRYFIRE2,
		ACT_SMG2_TOAUTO,
		ACT_SMG2_TOBURST,
		ACT_PHYSCANNON_UPGRADE,
		ACT_RANGE_ATTACK_AR1,
		ACT_RANGE_ATTACK_AR2,
		ACT_RANGE_ATTACK_AR2_LOW,
		ACT_RANGE_ATTACK_AR2_GRENADE,
		ACT_RANGE_ATTACK_HMG1,
		ACT_RANGE_ATTACK_ML,
		ACT_RANGE_ATTACK_SMG1,
		ACT_RANGE_ATTACK_SMG1_LOW,
		ACT_RANGE_ATTACK_SMG2,
		ACT_RANGE_ATTACK_SHOTGUN,
		ACT_RANGE_ATTACK_SHOTGUN_LOW,
		ACT_RANGE_ATTACK_PISTOL,
		ACT_RANGE_ATTACK_PISTOL_LOW,
		ACT_RANGE_ATTACK_SLAM,
		ACT_RANGE_ATTACK_TRIPWIRE,
		ACT_RANGE_ATTACK_THROW,
		ACT_RANGE_ATTACK_SNIPER_RIFLE,
		ACT_RANGE_ATTACK_RPG,
		ACT_MELEE_ATTACK_SWING,
		ACT_RANGE_AIM_LOW,
		ACT_RANGE_AIM_SMG1_LOW,
		ACT_RANGE_AIM_PISTOL_LOW,
		ACT_RANGE_AIM_AR2_LOW,
		ACT_COVER_PISTOL_LOW,
		ACT_COVER_SMG1_LOW,
		ACT_GESTURE_RANGE_ATTACK_AR1,
		ACT_GESTURE_RANGE_ATTACK_AR2,
		ACT_GESTURE_RANGE_ATTACK_AR2_GRENADE,
		ACT_GESTURE_RANGE_ATTACK_HMG1,
		ACT_GESTURE_RANGE_ATTACK_ML,
		ACT_GESTURE_RANGE_ATTACK_SMG1,
		ACT_GESTURE_RANGE_ATTACK_SMG1_LOW,
		ACT_GESTURE_RANGE_ATTACK_SMG2,
		ACT_GESTURE_RANGE_ATTACK_SHOTGUN,
		ACT_GESTURE_RANGE_ATTACK_PISTOL,
		ACT_GESTURE_RANGE_ATTACK_PISTOL_LOW,
		ACT_GESTURE_RANGE_ATTACK_SLAM,
		ACT_GESTURE_RANGE_ATTACK_TRIPWIRE,
		ACT_GESTURE_RANGE_ATTACK_THROW,
		ACT_GESTURE_RANGE_ATTACK_SNIPER_RIFLE,
		ACT_GESTURE_MELEE_ATTACK_SWING,
		ACT_IDLE_RIFLE,
		ACT_IDLE_SMG1,
		ACT_IDLE_ANGRY_SMG1,
		ACT_IDLE_PISTOL,
		ACT_IDLE_ANGRY_PISTOL,
		ACT_IDLE_ANGRY_SHOTGUN,
		ACT_IDLE_STEALTH_PISTOL,
		ACT_IDLE_PACKAGE,
		ACT_WALK_PACKAGE,
		ACT_IDLE_SUITCASE,
		ACT_WALK_SUITCASE,
		ACT_IDLE_SMG1_RELAXED,
		ACT_IDLE_SMG1_STIMULATED,
		ACT_WALK_RIFLE_RELAXED,
		ACT_RUN_RIFLE_RELAXED,
		ACT_WALK_RIFLE_STIMULATED,
		ACT_RUN_RIFLE_STIMULATED,
		ACT_IDLE_AIM_RIFLE_STIMULATED,
		ACT_WALK_AIM_RIFLE_STIMULATED,
		ACT_RUN_AIM_RIFLE_STIMULATED,
		ACT_IDLE_SHOTGUN_RELAXED,
		ACT_IDLE_SHOTGUN_STIMULATED,
		ACT_IDLE_SHOTGUN_AGITATED,
		ACT_WALK_ANGRY,
		ACT_POLICE_HARASS1,
		ACT_POLICE_HARASS2,
		ACT_IDLE_MANNEDGUN,
		ACT_IDLE_MELEE,
		ACT_IDLE_ANGRY_MELEE,
		ACT_IDLE_RPG_RELAXED,
		ACT_IDLE_RPG,
		ACT_IDLE_ANGRY_RPG,
		ACT_COVER_LOW_RPG,
		ACT_WALK_RPG,
		ACT_RUN_RPG,
		ACT_WALK_CROUCH_RPG,
		ACT_RUN_CROUCH_RPG,
		ACT_WALK_RPG_RELAXED,
		ACT_RUN_RPG_RELAXED,
		ACT_WALK_RIFLE,
		ACT_WALK_AIM_RIFLE,
		ACT_WALK_CROUCH_RIFLE,
		ACT_WALK_CROUCH_AIM_RIFLE,
		ACT_RUN_RIFLE,
		ACT_RUN_AIM_RIFLE,
		ACT_RUN_CROUCH_RIFLE,
		ACT_RUN_CROUCH_AIM_RIFLE,
		ACT_RUN_STEALTH_PISTOL,
		ACT_WALK_AIM_SHOTGUN,
		ACT_RUN_AIM_SHOTGUN,
		ACT_WALK_PISTOL,
		ACT_RUN_PISTOL,
		ACT_WALK_AIM_PISTOL,
		ACT_RUN_AIM_PISTOL,
		ACT_WALK_STEALTH_PISTOL,
		ACT_WALK_AIM_STEALTH_PISTOL,
		ACT_RUN_AIM_STEALTH_PISTOL,
		ACT_RELOAD_PISTOL,
		ACT_RELOAD_PISTOL_LOW,
		ACT_RELOAD_SMG1,
		ACT_RELOAD_SMG1_LOW,
		ACT_RELOAD_SHOTGUN,
		ACT_RELOAD_SHOTGUN_LOW,
		ACT_GESTURE_RELOAD,
		ACT_GESTURE_RELOAD_PISTOL,
		ACT_GESTURE_RELOAD_SMG1,
		ACT_GESTURE_RELOAD_SHOTGUN,
		ACT_BUSY_LEAN_LEFT,
		ACT_BUSY_LEAN_LEFT_ENTRY,
		ACT_BUSY_LEAN_LEFT_EXIT,
		ACT_BUSY_LEAN_BACK,
		ACT_BUSY_LEAN_BACK_ENTRY,
		ACT_BUSY_LEAN_BACK_EXIT,
		ACT_BUSY_SIT_GROUND,
		ACT_BUSY_SIT_GROUND_ENTRY,
		ACT_BUSY_SIT_GROUND_EXIT,
		ACT_BUSY_SIT_CHAIR,
		ACT_BUSY_SIT_CHAIR_ENTRY,
		ACT_BUSY_SIT_CHAIR_EXIT,
		ACT_BUSY_STAND,
		ACT_BUSY_QUEUE,
		ACT_DUCK_DODGE,
		ACT_DIE_BARNACLE_SWALLOW,
		ACT_GESTURE_BARNACLE_STRANGLE,
		ACT_PHYSCANNON_DETACH,
		ACT_PHYSCANNON_ANIMATE,
		ACT_PHYSCANNON_ANIMATE_PRE,
		ACT_PHYSCANNON_ANIMATE_POST,
		ACT_DIE_FRONTSIDE,
		ACT_DIE_RIGHTSIDE,
		ACT_DIE_BACKSIDE,
		ACT_DIE_LEFTSIDE,
		ACT_DIE_CROUCH_FRONTSIDE,
		ACT_DIE_CROUCH_RIGHTSIDE,
		ACT_DIE_CROUCH_BACKSIDE,
		ACT_DIE_CROUCH_LEFTSIDE,
		ACT_OPEN_DOOR,
		ACT_DI_ALYX_ZOMBIE_MELEE,
		ACT_DI_ALYX_ZOMBIE_TORSO_MELEE,
		ACT_DI_ALYX_HEADCRAB_MELEE,
		ACT_DI_ALYX_ANTLION,
		ACT_DI_ALYX_ZOMBIE_SHOTGUN64,
		ACT_DI_ALYX_ZOMBIE_SHOTGUN26,
		ACT_READINESS_RELAXED_TO_STIMULATED,
		ACT_READINESS_RELAXED_TO_STIMULATED_WALK,
		ACT_READINESS_AGITATED_TO_STIMULATED,
		ACT_READINESS_STIMULATED_TO_RELAXED,
		ACT_READINESS_PISTOL_RELAXED_TO_STIMULATED,
		ACT_READINESS_PISTOL_RELAXED_TO_STIMULATED_WALK,
		ACT_READINESS_PISTOL_AGITATED_TO_STIMULATED,
		ACT_READINESS_PISTOL_STIMULATED_TO_RELAXED,
		ACT_IDLE_CARRY,
		ACT_WALK_CARRY,
		ACT_STARTDYING,
		ACT_DYINGLOOP,
		ACT_DYINGTODEAD,
		ACT_RIDE_MANNED_GUN,
		ACT_VM_SPRINT_ENTER,
		ACT_VM_SPRINT_IDLE,
		ACT_VM_SPRINT_LEAVE,
		ACT_FIRE_START,
		ACT_FIRE_LOOP,
		ACT_FIRE_END,
		ACT_CROUCHING_GRENADEIDLE,
		ACT_CROUCHING_GRENADEREADY,
		ACT_CROUCHING_PRIMARYATTACK,
		ACT_OVERLAY_GRENADEIDLE,
		ACT_OVERLAY_GRENADEREADY,
		ACT_OVERLAY_PRIMARYATTACK,
		ACT_OVERLAY_SHIELD_UP,
		ACT_OVERLAY_SHIELD_DOWN,
		ACT_OVERLAY_SHIELD_UP_IDLE,
		ACT_OVERLAY_SHIELD_ATTACK,
		ACT_OVERLAY_SHIELD_KNOCKBACK,
		ACT_SHIELD_UP,
		ACT_SHIELD_DOWN,
		ACT_SHIELD_UP_IDLE,
		ACT_SHIELD_ATTACK,
		ACT_SHIELD_KNOCKBACK,
		ACT_CROUCHING_SHIELD_UP,
		ACT_CROUCHING_SHIELD_DOWN,
		ACT_CROUCHING_SHIELD_UP_IDLE,
		ACT_CROUCHING_SHIELD_ATTACK,
		ACT_CROUCHING_SHIELD_KNOCKBACK,
		ACT_TURNRIGHT45,
		ACT_TURNLEFT45,
		ACT_TURN,
		ACT_OBJ_ASSEMBLING,
		ACT_OBJ_DISMANTLING,
		ACT_OBJ_STARTUP,
		ACT_OBJ_RUNNING,
		ACT_OBJ_IDLE,
		ACT_OBJ_PLACING,
		ACT_OBJ_DETERIORATING,
		ACT_OBJ_UPGRADING,
		ACT_DEPLOY,
		ACT_DEPLOY_IDLE,
		ACT_UNDEPLOY,
		ACT_CROSSBOW_DRAW_UNLOADED,
		ACT_GAUSS_SPINUP,
		ACT_GAUSS_SPINCYCLE,
		ACT_VM_PRIMARYATTACK_SILENCED,
		ACT_VM_RELOAD_SILENCED,
		ACT_VM_DRYFIRE_SILENCED,
		ACT_VM_IDLE_SILENCED,
		ACT_VM_DRAW_SILENCED,
		ACT_VM_IDLE_EMPTY_LEFT,
		ACT_VM_DRYFIRE_LEFT,
		ACT_VM_IS_DRAW,
		ACT_VM_IS_HOLSTER,
		ACT_VM_IS_IDLE,
		ACT_VM_IS_PRIMARYATTACK,
		ACT_PLAYER_IDLE_FIRE,
		ACT_PLAYER_CROUCH_FIRE,
		ACT_PLAYER_CROUCH_WALK_FIRE,
		ACT_PLAYER_WALK_FIRE,
		ACT_PLAYER_RUN_FIRE,
		ACT_IDLETORUN,
		ACT_RUNTOIDLE,
		ACT_VM_DRAW_DEPLOYED,
		ACT_HL2MP_IDLE_MELEE,
		ACT_HL2MP_RUN_MELEE,
		ACT_HL2MP_IDLE_CROUCH_MELEE,
		ACT_HL2MP_WALK_CROUCH_MELEE,
		ACT_HL2MP_GESTURE_RANGE_ATTACK_MELEE,
		ACT_HL2MP_GESTURE_RELOAD_MELEE,
		ACT_HL2MP_JUMP_MELEE,
		ACT_VM_FIZZLE,
		ACT_MP_STAND_IDLE,
		ACT_MP_CROUCH_IDLE,
		ACT_MP_CROUCH_DEPLOYED_IDLE,
		ACT_MP_CROUCH_DEPLOYED,
		ACT_MP_DEPLOYED_IDLE,
		ACT_MP_RUN,
		ACT_MP_WALK,
		ACT_MP_AIRWALK,
		ACT_MP_CROUCHWALK,
		ACT_MP_SPRINT,
		ACT_MP_JUMP,
		ACT_MP_JUMP_START,
		ACT_MP_JUMP_FLOAT,
		ACT_MP_JUMP_LAND,
		ACT_MP_JUMP_IMPACT_N,
		ACT_MP_JUMP_IMPACT_E,
		ACT_MP_JUMP_IMPACT_W,
		ACT_MP_JUMP_IMPACT_S,
		ACT_MP_JUMP_IMPACT_TOP,
		ACT_MP_DOUBLEJUMP,
		ACT_MP_SWIM,
		ACT_MP_DEPLOYED,
		ACT_MP_SWIM_DEPLOYED,
		ACT_MP_VCD,
		ACT_MP_ATTACK_STAND_PRIMARYFIRE,
		ACT_MP_ATTACK_STAND_PRIMARYFIRE_DEPLOYED,
		ACT_MP_ATTACK_STAND_SECONDARYFIRE,
		ACT_MP_ATTACK_STAND_GRENADE,
		ACT_MP_ATTACK_CROUCH_PRIMARYFIRE,
		ACT_MP_ATTACK_CROUCH_PRIMARYFIRE_DEPLOYED,
		ACT_MP_ATTACK_CROUCH_SECONDARYFIRE,
		ACT_MP_ATTACK_CROUCH_GRENADE,
		ACT_MP_ATTACK_SWIM_PRIMARYFIRE,
		ACT_MP_ATTACK_SWIM_SECONDARYFIRE,
		ACT_MP_ATTACK_SWIM_GRENADE,
		ACT_MP_ATTACK_AIRWALK_PRIMARYFIRE,
		ACT_MP_ATTACK_AIRWALK_SECONDARYFIRE,
		ACT_MP_ATTACK_AIRWALK_GRENADE,
		ACT_MP_RELOAD_STAND,
		ACT_MP_RELOAD_STAND_LOOP,
		ACT_MP_RELOAD_STAND_END,
		ACT_MP_RELOAD_CROUCH,
		ACT_MP_RELOAD_CROUCH_LOOP,
		ACT_MP_RELOAD_CROUCH_END,
		ACT_MP_RELOAD_SWIM,
		ACT_MP_RELOAD_SWIM_LOOP,
		ACT_MP_RELOAD_SWIM_END,
		ACT_MP_RELOAD_AIRWALK,
		ACT_MP_RELOAD_AIRWALK_LOOP,
		ACT_MP_RELOAD_AIRWALK_END,
		ACT_MP_ATTACK_STAND_PREFIRE,
		ACT_MP_ATTACK_STAND_POSTFIRE,
		ACT_MP_ATTACK_STAND_STARTFIRE,
		ACT_MP_ATTACK_CROUCH_PREFIRE,
		ACT_MP_ATTACK_CROUCH_POSTFIRE,
		ACT_MP_ATTACK_SWIM_PREFIRE,
		ACT_MP_ATTACK_SWIM_POSTFIRE,
		ACT_MP_STAND_PRIMARY,
		ACT_MP_CROUCH_PRIMARY,
		ACT_MP_RUN_PRIMARY,
		ACT_MP_WALK_PRIMARY,
		ACT_MP_AIRWALK_PRIMARY,
		ACT_MP_CROUCHWALK_PRIMARY,
		ACT_MP_JUMP_PRIMARY,
		ACT_MP_JUMP_START_PRIMARY,
		ACT_MP_JUMP_FLOAT_PRIMARY,
		ACT_MP_JUMP_LAND_PRIMARY,
		ACT_MP_SWIM_PRIMARY,
		ACT_MP_DEPLOYED_PRIMARY,
		ACT_MP_SWIM_DEPLOYED_PRIMARY,
		ACT_MP_ATTACK_STAND_PRIMARY,
		ACT_MP_ATTACK_STAND_PRIMARY_DEPLOYED,
		ACT_MP_ATTACK_CROUCH_PRIMARY,
		ACT_MP_ATTACK_CROUCH_PRIMARY_DEPLOYED,
		ACT_MP_ATTACK_SWIM_PRIMARY,
		ACT_MP_ATTACK_AIRWALK_PRIMARY,
		ACT_MP_RELOAD_STAND_PRIMARY,
		ACT_MP_RELOAD_STAND_PRIMARY_LOOP,
		ACT_MP_RELOAD_STAND_PRIMARY_END,
		ACT_MP_RELOAD_CROUCH_PRIMARY,
		ACT_MP_RELOAD_CROUCH_PRIMARY_LOOP,
		ACT_MP_RELOAD_CROUCH_PRIMARY_END,
		ACT_MP_RELOAD_SWIM_PRIMARY,
		ACT_MP_RELOAD_SWIM_PRIMARY_LOOP,
		ACT_MP_RELOAD_SWIM_PRIMARY_END,
		ACT_MP_RELOAD_AIRWALK_PRIMARY,
		ACT_MP_RELOAD_AIRWALK_PRIMARY_LOOP,
		ACT_MP_RELOAD_AIRWALK_PRIMARY_END,
		ACT_MP_ATTACK_STAND_GRENADE_PRIMARY,
		ACT_MP_ATTACK_CROUCH_GRENADE_PRIMARY,
		ACT_MP_ATTACK_SWIM_GRENADE_PRIMARY,
		ACT_MP_ATTACK_AIRWALK_GRENADE_PRIMARY,
		ACT_MP_STAND_SECONDARY,
		ACT_MP_CROUCH_SECONDARY,
		ACT_MP_RUN_SECONDARY,
		ACT_MP_WALK_SECONDARY,
		ACT_MP_AIRWALK_SECONDARY,
		ACT_MP_CROUCHWALK_SECONDARY,
		ACT_MP_JUMP_SECONDARY,
		ACT_MP_JUMP_START_SECONDARY,
		ACT_MP_JUMP_FLOAT_SECONDARY,
		ACT_MP_JUMP_LAND_SECONDARY,
		ACT_MP_SWIM_SECONDARY,
		ACT_MP_ATTACK_STAND_SECONDARY,
		ACT_MP_ATTACK_CROUCH_SECONDARY,
		ACT_MP_ATTACK_SWIM_SECONDARY,
		ACT_MP_ATTACK_AIRWALK_SECONDARY,
		ACT_MP_RELOAD_STAND_SECONDARY,
		ACT_MP_RELOAD_STAND_SECONDARY_LOOP,
		ACT_MP_RELOAD_STAND_SECONDARY_END,
		ACT_MP_RELOAD_CROUCH_SECONDARY,
		ACT_MP_RELOAD_CROUCH_SECONDARY_LOOP,
		ACT_MP_RELOAD_CROUCH_SECONDARY_END,
		ACT_MP_RELOAD_SWIM_SECONDARY,
		ACT_MP_RELOAD_SWIM_SECONDARY_LOOP,
		ACT_MP_RELOAD_SWIM_SECONDARY_END,
		ACT_MP_RELOAD_AIRWALK_SECONDARY,
		ACT_MP_RELOAD_AIRWALK_SECONDARY_LOOP,
		ACT_MP_RELOAD_AIRWALK_SECONDARY_END,
		ACT_MP_ATTACK_STAND_GRENADE_SECONDARY,
		ACT_MP_ATTACK_CROUCH_GRENADE_SECONDARY,
		ACT_MP_ATTACK_SWIM_GRENADE_SECONDARY,
		ACT_MP_ATTACK_AIRWALK_GRENADE_SECONDARY,
		ACT_MP_STAND_MELEE,
		ACT_MP_CROUCH_MELEE,
		ACT_MP_RUN_MELEE,
		ACT_MP_WALK_MELEE,
		ACT_MP_AIRWALK_MELEE,
		ACT_MP_CROUCHWALK_MELEE,
		ACT_MP_JUMP_MELEE,
		ACT_MP_JUMP_START_MELEE,
		ACT_MP_JUMP_FLOAT_MELEE,
		ACT_MP_JUMP_LAND_MELEE,
		ACT_MP_SWIM_MELEE,
		ACT_MP_ATTACK_STAND_MELEE,
		ACT_MP_ATTACK_STAND_MELEE_SECONDARY,
		ACT_MP_ATTACK_CROUCH_MELEE,
		ACT_MP_ATTACK_CROUCH_MELEE_SECONDARY,
		ACT_MP_ATTACK_SWIM_MELEE,
		ACT_MP_ATTACK_AIRWALK_MELEE,
		ACT_MP_ATTACK_STAND_GRENADE_MELEE,
		ACT_MP_ATTACK_CROUCH_GRENADE_MELEE,
		ACT_MP_ATTACK_SWIM_GRENADE_MELEE,
		ACT_MP_ATTACK_AIRWALK_GRENADE_MELEE,
		ACT_MP_STAND_ITEM1,
		ACT_MP_CROUCH_ITEM1,
		ACT_MP_RUN_ITEM1,
		ACT_MP_WALK_ITEM1,
		ACT_MP_AIRWALK_ITEM1,
		ACT_MP_CROUCHWALK_ITEM1,
		ACT_MP_JUMP_ITEM1,
		ACT_MP_JUMP_START_ITEM1,
		ACT_MP_JUMP_FLOAT_ITEM1,
		ACT_MP_JUMP_LAND_ITEM1,
		ACT_MP_SWIM_ITEM1,
		ACT_MP_ATTACK_STAND_ITEM1,
		ACT_MP_ATTACK_STAND_ITEM1_SECONDARY,
		ACT_MP_ATTACK_CROUCH_ITEM1,
		ACT_MP_ATTACK_CROUCH_ITEM1_SECONDARY,
		ACT_MP_ATTACK_SWIM_ITEM1,
		ACT_MP_ATTACK_AIRWALK_ITEM1,
		ACT_MP_STAND_ITEM2,
		ACT_MP_CROUCH_ITEM2,
		ACT_MP_RUN_ITEM2,
		ACT_MP_WALK_ITEM2,
		ACT_MP_AIRWALK_ITEM2,
		ACT_MP_CROUCHWALK_ITEM2,
		ACT_MP_JUMP_ITEM2,
		ACT_MP_JUMP_START_ITEM2,
		ACT_MP_JUMP_FLOAT_ITEM2,
		ACT_MP_JUMP_LAND_ITEM2,
		ACT_MP_SWIM_ITEM2,
		ACT_MP_ATTACK_STAND_ITEM2,
		ACT_MP_ATTACK_STAND_ITEM2_SECONDARY,
		ACT_MP_ATTACK_CROUCH_ITEM2,
		ACT_MP_ATTACK_CROUCH_ITEM2_SECONDARY,
		ACT_MP_ATTACK_SWIM_ITEM2,
		ACT_MP_ATTACK_AIRWALK_ITEM2,
		ACT_MP_GESTURE_FLINCH,
		ACT_MP_GESTURE_FLINCH_PRIMARY,
		ACT_MP_GESTURE_FLINCH_SECONDARY,
		ACT_MP_GESTURE_FLINCH_MELEE,
		ACT_MP_GESTURE_FLINCH_ITEM1,
		ACT_MP_GESTURE_FLINCH_ITEM2,
		ACT_MP_GESTURE_FLINCH_HEAD,
		ACT_MP_GESTURE_FLINCH_CHEST,
		ACT_MP_GESTURE_FLINCH_STOMACH,
		ACT_MP_GESTURE_FLINCH_LEFTARM,
		ACT_MP_GESTURE_FLINCH_RIGHTARM,
		ACT_MP_GESTURE_FLINCH_LEFTLEG,
		ACT_MP_GESTURE_FLINCH_RIGHTLEG,
		ACT_MP_GRENADE1_DRAW,
		ACT_MP_GRENADE1_IDLE,
		ACT_MP_GRENADE1_ATTACK,
		ACT_MP_GRENADE2_DRAW,
		ACT_MP_GRENADE2_IDLE,
		ACT_MP_GRENADE2_ATTACK,
		ACT_MP_PRIMARY_GRENADE1_DRAW,
		ACT_MP_PRIMARY_GRENADE1_IDLE,
		ACT_MP_PRIMARY_GRENADE1_ATTACK,
		ACT_MP_PRIMARY_GRENADE2_DRAW,
		ACT_MP_PRIMARY_GRENADE2_IDLE,
		ACT_MP_PRIMARY_GRENADE2_ATTACK,
		ACT_MP_SECONDARY_GRENADE1_DRAW,
		ACT_MP_SECONDARY_GRENADE1_IDLE,
		ACT_MP_SECONDARY_GRENADE1_ATTACK,
		ACT_MP_SECONDARY_GRENADE2_DRAW,
		ACT_MP_SECONDARY_GRENADE2_IDLE,
		ACT_MP_SECONDARY_GRENADE2_ATTACK,
		ACT_MP_MELEE_GRENADE1_DRAW,
		ACT_MP_MELEE_GRENADE1_IDLE,
		ACT_MP_MELEE_GRENADE1_ATTACK,
		ACT_MP_MELEE_GRENADE2_DRAW,
		ACT_MP_MELEE_GRENADE2_IDLE,
		ACT_MP_MELEE_GRENADE2_ATTACK,
		ACT_MP_ITEM1_GRENADE1_DRAW,
		ACT_MP_ITEM1_GRENADE1_IDLE,
		ACT_MP_ITEM1_GRENADE1_ATTACK,
		ACT_MP_ITEM1_GRENADE2_DRAW,
		ACT_MP_ITEM1_GRENADE2_IDLE,
		ACT_MP_ITEM1_GRENADE2_ATTACK,
		ACT_MP_ITEM2_GRENADE1_DRAW,
		ACT_MP_ITEM2_GRENADE1_IDLE,
		ACT_MP_ITEM2_GRENADE1_ATTACK,
		ACT_MP_ITEM2_GRENADE2_DRAW,
		ACT_MP_ITEM2_GRENADE2_IDLE,
		ACT_MP_ITEM2_GRENADE2_ATTACK,
		ACT_MP_STAND_BUILDING,
		ACT_MP_CROUCH_BUILDING,
		ACT_MP_RUN_BUILDING,
		ACT_MP_WALK_BUILDING,
		ACT_MP_AIRWALK_BUILDING,
		ACT_MP_CROUCHWALK_BUILDING,
		ACT_MP_JUMP_BUILDING,
		ACT_MP_JUMP_START_BUILDING,
		ACT_MP_JUMP_FLOAT_BUILDING,
		ACT_MP_JUMP_LAND_BUILDING,
		ACT_MP_SWIM_BUILDING,
		ACT_MP_ATTACK_STAND_BUILDING,
		ACT_MP_ATTACK_CROUCH_BUILDING,
		ACT_MP_ATTACK_SWIM_BUILDING,
		ACT_MP_ATTACK_AIRWALK_BUILDING,
		ACT_MP_ATTACK_STAND_GRENADE_BUILDING,
		ACT_MP_ATTACK_CROUCH_GRENADE_BUILDING,
		ACT_MP_ATTACK_SWIM_GRENADE_BUILDING,
		ACT_MP_ATTACK_AIRWALK_GRENADE_BUILDING,
		ACT_MP_STAND_PDA,
		ACT_MP_CROUCH_PDA,
		ACT_MP_RUN_PDA,
		ACT_MP_WALK_PDA,
		ACT_MP_AIRWALK_PDA,
		ACT_MP_CROUCHWALK_PDA,
		ACT_MP_JUMP_PDA,
		ACT_MP_JUMP_START_PDA,
		ACT_MP_JUMP_FLOAT_PDA,
		ACT_MP_JUMP_LAND_PDA,
		ACT_MP_SWIM_PDA,
		ACT_MP_ATTACK_STAND_PDA,
		ACT_MP_ATTACK_SWIM_PDA,
		ACT_MP_GESTURE_VC_HANDMOUTH,
		ACT_MP_GESTURE_VC_FINGERPOINT,
		ACT_MP_GESTURE_VC_FISTPUMP,
		ACT_MP_GESTURE_VC_THUMBSUP,
		ACT_MP_GESTURE_VC_NODYES,
		ACT_MP_GESTURE_VC_NODNO,
		ACT_MP_GESTURE_VC_HANDMOUTH_PRIMARY,
		ACT_MP_GESTURE_VC_FINGERPOINT_PRIMARY,
		ACT_MP_GESTURE_VC_FISTPUMP_PRIMARY,
		ACT_MP_GESTURE_VC_THUMBSUP_PRIMARY,
		ACT_MP_GESTURE_VC_NODYES_PRIMARY,
		ACT_MP_GESTURE_VC_NODNO_PRIMARY,
		ACT_MP_GESTURE_VC_HANDMOUTH_SECONDARY,
		ACT_MP_GESTURE_VC_FINGERPOINT_SECONDARY,
		ACT_MP_GESTURE_VC_FISTPUMP_SECONDARY,
		ACT_MP_GESTURE_VC_THUMBSUP_SECONDARY,
		ACT_MP_GESTURE_VC_NODYES_SECONDARY,
		ACT_MP_GESTURE_VC_NODNO_SECONDARY,
		ACT_MP_GESTURE_VC_HANDMOUTH_MELEE,
		ACT_MP_GESTURE_VC_FINGERPOINT_MELEE,
		ACT_MP_GESTURE_VC_FISTPUMP_MELEE,
		ACT_MP_GESTURE_VC_THUMBSUP_MELEE,
		ACT_MP_GESTURE_VC_NODYES_MELEE,
		ACT_MP_GESTURE_VC_NODNO_MELEE,
		ACT_MP_GESTURE_VC_HANDMOUTH_ITEM1,
		ACT_MP_GESTURE_VC_FINGERPOINT_ITEM1,
		ACT_MP_GESTURE_VC_FISTPUMP_ITEM1,
		ACT_MP_GESTURE_VC_THUMBSUP_ITEM1,
		ACT_MP_GESTURE_VC_NODYES_ITEM1,
		ACT_MP_GESTURE_VC_NODNO_ITEM1,
		ACT_MP_GESTURE_VC_HANDMOUTH_ITEM2,
		ACT_MP_GESTURE_VC_FINGERPOINT_ITEM2,
		ACT_MP_GESTURE_VC_FISTPUMP_ITEM2,
		ACT_MP_GESTURE_VC_THUMBSUP_ITEM2,
		ACT_MP_GESTURE_VC_NODYES_ITEM2,
		ACT_MP_GESTURE_VC_NODNO_ITEM2,
		ACT_MP_GESTURE_VC_HANDMOUTH_BUILDING,
		ACT_MP_GESTURE_VC_FINGERPOINT_BUILDING,
		ACT_MP_GESTURE_VC_FISTPUMP_BUILDING,
		ACT_MP_GESTURE_VC_THUMBSUP_BUILDING,
		ACT_MP_GESTURE_VC_NODYES_BUILDING,
		ACT_MP_GESTURE_VC_NODNO_BUILDING,
		ACT_MP_GESTURE_VC_HANDMOUTH_PDA,
		ACT_MP_GESTURE_VC_FINGERPOINT_PDA,
		ACT_MP_GESTURE_VC_FISTPUMP_PDA,
		ACT_MP_GESTURE_VC_THUMBSUP_PDA,
		ACT_MP_GESTURE_VC_NODYES_PDA,
		ACT_MP_GESTURE_VC_NODNO_PDA,
		ACT_VM_UNUSABLE,
		ACT_VM_UNUSABLE_TO_USABLE,
		ACT_VM_USABLE_TO_UNUSABLE,
		ACT_PRIMARY_VM_DRAW,
		ACT_PRIMARY_VM_HOLSTER,
		ACT_PRIMARY_VM_IDLE,
		ACT_PRIMARY_VM_PULLBACK,
		ACT_PRIMARY_VM_PRIMARYATTACK,
		ACT_PRIMARY_VM_SECONDARYATTACK,
		ACT_PRIMARY_VM_RELOAD,
		ACT_PRIMARY_VM_DRYFIRE,
		ACT_PRIMARY_VM_IDLE_TO_LOWERED,
		ACT_PRIMARY_VM_IDLE_LOWERED,
		ACT_PRIMARY_VM_LOWERED_TO_IDLE,
		ACT_SECONDARY_VM_DRAW,
		ACT_SECONDARY_VM_HOLSTER,
		ACT_SECONDARY_VM_IDLE,
		ACT_SECONDARY_VM_PULLBACK,
		ACT_SECONDARY_VM_PRIMARYATTACK,
		ACT_SECONDARY_VM_SECONDARYATTACK,
		ACT_SECONDARY_VM_RELOAD,
		ACT_SECONDARY_VM_DRYFIRE,
		ACT_SECONDARY_VM_IDLE_TO_LOWERED,
		ACT_SECONDARY_VM_IDLE_LOWERED,
		ACT_SECONDARY_VM_LOWERED_TO_IDLE,
		ACT_MELEE_VM_DRAW,
		ACT_MELEE_VM_HOLSTER,
		ACT_MELEE_VM_IDLE,
		ACT_MELEE_VM_PULLBACK,
		ACT_MELEE_VM_PRIMARYATTACK,
		ACT_MELEE_VM_SECONDARYATTACK,
		ACT_MELEE_VM_RELOAD,
		ACT_MELEE_VM_DRYFIRE,
		ACT_MELEE_VM_IDLE_TO_LOWERED,
		ACT_MELEE_VM_IDLE_LOWERED,
		ACT_MELEE_VM_LOWERED_TO_IDLE,
		ACT_PDA_VM_DRAW,
		ACT_PDA_VM_HOLSTER,
		ACT_PDA_VM_IDLE,
		ACT_PDA_VM_PULLBACK,
		ACT_PDA_VM_PRIMARYATTACK,
		ACT_PDA_VM_SECONDARYATTACK,
		ACT_PDA_VM_RELOAD,
		ACT_PDA_VM_DRYFIRE,
		ACT_PDA_VM_IDLE_TO_LOWERED,
		ACT_PDA_VM_IDLE_LOWERED,
		ACT_PDA_VM_LOWERED_TO_IDLE,
		ACT_ITEM1_VM_DRAW,
		ACT_ITEM1_VM_HOLSTER,
		ACT_ITEM1_VM_IDLE,
		ACT_ITEM1_VM_PULLBACK,
		ACT_ITEM1_VM_PRIMARYATTACK,
		ACT_ITEM1_VM_SECONDARYATTACK,
		ACT_ITEM1_VM_RELOAD,
		ACT_ITEM1_VM_DRYFIRE,
		ACT_ITEM1_VM_IDLE_TO_LOWERED,
		ACT_ITEM1_VM_IDLE_LOWERED,
		ACT_ITEM1_VM_LOWERED_TO_IDLE,
		ACT_ITEM2_VM_DRAW,
		ACT_ITEM2_VM_HOLSTER,
		ACT_ITEM2_VM_IDLE,
		ACT_ITEM2_VM_PULLBACK,
		ACT_ITEM2_VM_PRIMARYATTACK,
		ACT_ITEM2_VM_SECONDARYATTACK,
		ACT_ITEM2_VM_RELOAD,
		ACT_ITEM2_VM_DRYFIRE,
		ACT_ITEM2_VM_IDLE_TO_LOWERED,
		ACT_ITEM2_VM_IDLE_LOWERED,
		ACT_ITEM2_VM_LOWERED_TO_IDLE,
		ACT_RELOAD_SUCCEED,
		ACT_RELOAD_FAIL,
		ACT_WALK_AIM_AUTOGUN,
		ACT_RUN_AIM_AUTOGUN,
		ACT_IDLE_AUTOGUN,
		ACT_IDLE_AIM_AUTOGUN,
		ACT_RELOAD_AUTOGUN,
		ACT_CROUCH_IDLE_AUTOGUN,
		ACT_RANGE_ATTACK_AUTOGUN,
		ACT_JUMP_AUTOGUN,
		ACT_IDLE_AIM_PISTOL,
		ACT_WALK_AIM_DUAL,
		ACT_RUN_AIM_DUAL,
		ACT_IDLE_DUAL,
		ACT_IDLE_AIM_DUAL,
		ACT_RELOAD_DUAL,
		ACT_CROUCH_IDLE_DUAL,
		ACT_RANGE_ATTACK_DUAL,
		ACT_JUMP_DUAL,
		ACT_IDLE_SHOTGUN,
		ACT_IDLE_AIM_SHOTGUN,
		ACT_CROUCH_IDLE_SHOTGUN,
		ACT_JUMP_SHOTGUN,
		ACT_IDLE_AIM_RIFLE,
		ACT_RELOAD_RIFLE,
		ACT_CROUCH_IDLE_RIFLE,
		ACT_RANGE_ATTACK_RIFLE,
		ACT_JUMP_RIFLE,
		ACT_SLEEP,
		ACT_WAKE,
		ACT_FLICK_LEFT,
		ACT_FLICK_LEFT_MIDDLE,
		ACT_FLICK_RIGHT_MIDDLE,
		ACT_FLICK_RIGHT,
		ACT_SPINAROUND,
		ACT_PREP_TO_FIRE,
		ACT_FIRE,
		ACT_FIRE_RECOVER,
		ACT_SPRAY,
		ACT_PREP_EXPLODE,
		ACT_EXPLODE,
		ACT_DOTA_IDLE,
		ACT_DOTA_RUN,
		ACT_DOTA_ATTACK,
		ACT_DOTA_ATTACK_EVENT,
		ACT_DOTA_DIE,
		ACT_DOTA_FLINCH,
		ACT_DOTA_DISABLED,
		ACT_DOTA_CAST_ABILITY_1,
		ACT_DOTA_CAST_ABILITY_2,
		ACT_DOTA_CAST_ABILITY_3,
		ACT_DOTA_CAST_ABILITY_4,
		ACT_DOTA_OVERRIDE_ABILITY_1,
		ACT_DOTA_OVERRIDE_ABILITY_2,
		ACT_DOTA_OVERRIDE_ABILITY_3,
		ACT_DOTA_OVERRIDE_ABILITY_4,
		ACT_DOTA_CHANNEL_ABILITY_1,
		ACT_DOTA_CHANNEL_ABILITY_2,
		ACT_DOTA_CHANNEL_ABILITY_3,
		ACT_DOTA_CHANNEL_ABILITY_4,
		ACT_DOTA_CHANNEL_END_ABILITY_1,
		ACT_DOTA_CHANNEL_END_ABILITY_2,
		ACT_DOTA_CHANNEL_END_ABILITY_3,
		ACT_DOTA_CHANNEL_END_ABILITY_4,
		ACT_MP_RUN_SPEEDPAINT,
		ACT_MP_LONG_FALL,
		ACT_MP_TRACTORBEAM_FLOAT,
		ACT_MP_DEATH_CRUSH,
		ACT_MP_RUN_SPEEDPAINT_PRIMARY,
		ACT_MP_DROWNING_PRIMARY,
		ACT_MP_LONG_FALL_PRIMARY,
		ACT_MP_TRACTORBEAM_FLOAT_PRIMARY,
		ACT_MP_DEATH_CRUSH_PRIMARY,
		ACT_DIE_STAND,
		ACT_DIE_STAND_HEADSHOT,
		ACT_DIE_CROUCH,
		ACT_DIE_CROUCH_HEADSHOT,
		ACT_CSGO_NULL,
		ACT_CSGO_DEFUSE,
		ACT_CSGO_DEFUSE_WITH_KIT,
		ACT_CSGO_FLASHBANG_REACTION,
		ACT_CSGO_FIRE_PRIMARY,
		ACT_CSGO_FIRE_PRIMARY_OPT_1,
		ACT_CSGO_FIRE_PRIMARY_OPT_2,
		ACT_CSGO_FIRE_SECONDARY,
		ACT_CSGO_FIRE_SECONDARY_OPT_1,
		ACT_CSGO_FIRE_SECONDARY_OPT_2,
		ACT_CSGO_RELOAD,
		ACT_CSGO_RELOAD_START,
		ACT_CSGO_RELOAD_LOOP,
		ACT_CSGO_RELOAD_END,
		ACT_CSGO_OPERATE,
		ACT_CSGO_DEPLOY,
		ACT_CSGO_CATCH,
		ACT_CSGO_SILENCER_DETACH,
		ACT_CSGO_SILENCER_ATTACH,
		ACT_CSGO_TWITCH,
		ACT_CSGO_TWITCH_BUYZONE,
		ACT_CSGO_PLANT_BOMB,
		ACT_CSGO_IDLE_TURN_BALANCEADJUST,
		ACT_CSGO_IDLE_ADJUST_STOPPEDMOVING,
		ACT_CSGO_ALIVE_LOOP,
		ACT_CSGO_FLINCH,
		ACT_CSGO_FLINCH_HEAD,
		ACT_CSGO_FLINCH_MOLOTOV,
		ACT_CSGO_JUMP,
		ACT_CSGO_FALL,
		ACT_CSGO_CLIMB_LADDER,
		ACT_CSGO_LAND_LIGHT,
		ACT_CSGO_LAND_HEAVY,
		ACT_CSGO_EXIT_LADDER_TOP,
		ACT_CSGO_EXIT_LADDER_BOTTOM,
	};

	enum ItemDefinitionIndex : int
	{
		WEAPON_DEAGLE = 1,
		WEAPON_ELITE = 2,
		WEAPON_FIVESEVEN = 3,
		WEAPON_GLOCK = 4,
		WEAPON_AK47 = 7,
		WEAPON_AUG = 8,
		WEAPON_AWP = 9,
		WEAPON_FAMAS = 10,
		WEAPON_G3SG1 = 11,
		WEAPON_GALILAR = 13,
		WEAPON_M249 = 14,
		WEAPON_M4A1 = 16,
		WEAPON_MAC10 = 17,
		WEAPON_P90 = 19,
		WEAPON_UMP45 = 24,
		WEAPON_XM1014 = 25,
		WEAPON_BIZON = 26,
		WEAPON_MAG7 = 27,
		WEAPON_NEGEV = 28,
		WEAPON_SAWEDOFF = 29,
		WEAPON_TEC9 = 30,
		WEAPON_TASER = 31,
		WEAPON_HKP2000 = 32,
		WEAPON_MP7 = 33,
		WEAPON_MP9 = 34,
		WEAPON_NOVA = 35,
		WEAPON_P250 = 36,
		WEAPON_SCAR20 = 38,
		WEAPON_SG556 = 39,
		WEAPON_SSG08 = 40,
		WEAPON_KNIFE_CT = 42,
		WEAPON_FLASHBANG = 43,
		WEAPON_HEGRENADE = 44,
		WEAPON_SMOKEGRENADE = 45,
		WEAPON_MOLOTOV = 46,
		WEAPON_DECOY = 47,
		WEAPON_INCGRENADE = 48,
		WEAPON_C4 = 49,
		WEAPON_KNIFE_T = 59,
		WEAPON_M4A1_SILENCER = 60,
		WEAPON_USP_SILENCER = 61,
		WEAPON_CZ75A = 63,
		WEAPON_REVOLVER = 64,
		WEAPON_KNIFE_BAYONET = 500,
		WEAPON_KNIFE_FLIP = 505,
		WEAPON_KNIFE_GUT = 506,
		WEAPON_KNIFE_KARAMBIT = 507,
		WEAPON_KNIFE_M9_BAYONET = 508,
		WEAPON_KNIFE_TACTICAL = 509,
		WEAPON_KNIFE_FALCHION = 512,
		WEAPON_KNIFE_BOWIE = 514,
		WEAPON_KNIFE_BUTTERFLY = 515,
		WEAPON_KNIFE_PUSH = 516
	};

	
	class CBaseAnimating
	{
	public:
		std::array<float, 24>* m_flPoseParameter()
		{
			static int offset = 0;
			if (!offset)
				offset = OFFSETS::m_flPoseParameter;
			return (std::array<float, 24>*)((uintptr_t)this + offset);
		}
		model_t* GetModel()
		{
			void* pRenderable = reinterpret_cast<void*>(uintptr_t(this) + 0x4);
			typedef model_t* (__thiscall* fnGetModel)(void*);

			return VMT::VMTHookManager::GetFunction<fnGetModel>(pRenderable, 8)(pRenderable);
		}
		void SetBoneMatrix(matrix3x4_t* boneMatrix)
		{
			//Offset found in C_BaseAnimating::GetBoneTransform, string search ankle_L and a function below is the right one
			const auto model = this->GetModel();
			if (!model)
				return;

			matrix3x4_t* matrix = *(matrix3x4_t**)((DWORD)this + 9880);
			studiohdr_t *hdr = INTERFACES::ModelInfo->GetStudioModel(model);
			if (!hdr)
				return;
			int size = hdr->numbones;
			if (matrix) {
				for (int i = 0; i < size; i++)
					memcpy(matrix + i, boneMatrix + i, sizeof(matrix3x4_t));
			}
		}
		void GetDirectBoneMatrix(matrix3x4_t* boneMatrix)
		{
			const auto model = this->GetModel();
			if (!model)
				return;

			matrix3x4_t* matrix = *(matrix3x4_t**)((DWORD)this + 9880);
			studiohdr_t *hdr = INTERFACES::ModelInfo->GetStudioModel(model);
			if (!hdr)
				return;
			int size = hdr->numbones;
			if (matrix) {
				for (int i = 0; i < size; i++)
					memcpy(boneMatrix + i, matrix + i, sizeof(matrix3x4_t));
			}
		}
	};

	class CBaseEntity
	{
	public:
		int GetHealth()
		{
			return *reinterpret_cast<int*>(uintptr_t(this) + OFFSETS::m_iHealth);
		}
		Vector GetEyePosition(void)
		{
			return GetVecOrigin() + *(Vector*)((DWORD)this + OFFSETS::m_vecViewOffset1);
		}
		int GetFlags()
		{
			return *reinterpret_cast<int*>(uintptr_t(this) + OFFSETS::m_fFlags);
		}
		void SetFlags(int flags)
		{
			*reinterpret_cast<int*>(uintptr_t(this) + OFFSETS::m_fFlags) = flags;
		}
		int GetLifeState()
		{
			return *reinterpret_cast<int*>(uintptr_t(this) + OFFSETS::m_lifeState);
		}
		int GetTeam()
		{
			return *reinterpret_cast<int*>(uintptr_t(this) + OFFSETS::m_iTeamNum);
		}
		bool IsAlive()
		{
			return this->GetLifeState() == 0;
		}
		int GetObserverMode()
		{
			return *reinterpret_cast<int*>(uintptr_t(this) + OFFSETS::m_iObserverMode);
		}
		int SetObserverMode(int mode)
		{
			return *reinterpret_cast<int*>(uintptr_t(this) + OFFSETS::m_iObserverMode) = mode;
		}
		bool GetIsScoped()
		{
			return *reinterpret_cast<bool*>(uintptr_t(this) + OFFSETS::m_bIsScoped);
		}
		Vector GetVelocity()
		{
			return *reinterpret_cast<Vector*>(uintptr_t(this) + OFFSETS::m_vecVelocity);
		}
		void SetVelocity(Vector velocity)
		{
			*reinterpret_cast<Vector*>(uintptr_t(this) + OFFSETS::m_vecVelocity) = velocity;
		}
		int GetMoney()
		{
			return *reinterpret_cast<int*>(uintptr_t(this) + OFFSETS::m_iAccount);
		}
		float GetLowerBodyYaw()
		{
			return *reinterpret_cast<float*>(uintptr_t(this) + OFFSETS::m_flLowerBodyYawTarget);
		}
		Vector GetVecOrigin()
		{
			return *reinterpret_cast<Vector*>(uintptr_t(this) + OFFSETS::m_vecOrigin);
		}
		float GetOrigin()
		{
			return((DWORD)this + OFFSETS::m_vecOrigin);
		}

		Vector& GetAbsOrigin()
		{
			typedef Vector& (__thiscall* OriginalFn)(void*);
			return ((OriginalFn)VMT::VMTHookManager::GetFunction<OriginalFn>(this, 10))(this);
		}
		int GetTickBase()
		{
			return *reinterpret_cast<int*>(uintptr_t(this) + OFFSETS::m_nTickBase);
		}
		bool GetIsDormant()
		{
			
			return *reinterpret_cast<bool*>(uintptr_t(this) + OFFSETS::m_bDormant);
		}
		CBaseAnimState* GetAnimState()
		{
			return *reinterpret_cast<CBaseAnimState**>(uintptr_t(this) + OFFSETS::animstate);
		}
		Collideable* GetCollideable()
		{
			return (Collideable*)((DWORD)this + OFFSETS::m_Collision);
		}
		void GetRenderBounds(Vector& mins, Vector& maxs)
		{
			void* pRenderable = (void*)(this + 0x4);
			typedef void(__thiscall* Fn)(void*, Vector&, Vector&);
			VMT::VMTHookManager::GetFunction<Fn>(pRenderable, 17)(pRenderable, mins, maxs);
		}
		int GetIndex()
		{
			return *reinterpret_cast<int*>(uintptr_t(this) + 0x64);
		}
		CAnimationLayer& GetAnimOverlay(int Index)
		{
			return (*(CAnimationLayer**)((DWORD)this + 0x2970))[Index];
		}
		void SetAnimOverlay(int Index, CAnimationLayer layer)
		{
			(*(CAnimationLayer**)((DWORD)this + 0x2970))[Index] = layer;
		}
		int CBaseEntity::GetSequenceActivity(int sequence)
		{
			const auto model = GetModel();
			if (!model)
				return -1;

			const auto hdr = INTERFACES::ModelInfo->GetStudioModel(model);
			if (!hdr)
				return -1;

			static auto offset = (DWORD)UTILS::FindSignature("client.dll", "55 8B EC 83 7D 08 FF 56 8B F1 74 3D");
			static auto GetSequenceActivity = reinterpret_cast<int(__fastcall*)(void*, SDK::studiohdr_t*, int)>(offset);

			return GetSequenceActivity(this, hdr, sequence);
		}
		Vector GetEyeAngles()
		{
			return *reinterpret_cast<Vector*>(uintptr_t(this) + OFFSETS::m_angEyeAngles);
		}
		QAngle* EasyEyeAngles()
		{
			return (QAngle*)((uintptr_t)this + OFFSETS::m_angEyeAngles);
		}
		void SetEyeAngles(Vector angles)
		{
			*reinterpret_cast<Vector*>(uintptr_t(this) + OFFSETS::m_angEyeAngles) = angles;
		}
		float GetSimTime()
		{
			return *reinterpret_cast<float*>(uintptr_t(this) + OFFSETS::m_flSimulationTime);
		}
		Vector GetViewOffset()
		{
			return *reinterpret_cast<Vector*>(uintptr_t(this) + OFFSETS::m_vecViewOffset);
		}
		model_t* GetModel()
		{
			void* pRenderable = reinterpret_cast<void*>(uintptr_t(this) + 0x4);
			typedef model_t* (__thiscall* fnGetModel)(void*);

			return VMT::VMTHookManager::GetFunction<fnGetModel>(pRenderable, 8)(pRenderable);
		}
		matrix3x4_t GetBoneMatrix(int BoneID)
		{
			matrix3x4_t matrix;

			auto offset = *reinterpret_cast<uintptr_t*>(uintptr_t(this) + OFFSETS::m_dwBoneMatrix);
			if (offset)
				matrix = *reinterpret_cast<matrix3x4_t*>(offset + 0x30 * BoneID);

			return matrix;
		}
		Vector GetBonePosition(int i)
		{
			matrix3x4_t matrix[128];
			if (this->SetupBones(matrix, 128, BONE_USED_BY_ANYTHING, GetTickCount64()))
			{
				return Vector(matrix[i][0][3], matrix[i][1][3], matrix[i][2][3]);
			}
			return Vector(0, 0, 0);
		}
		Vector GetPunchAngles()
		{
			return *reinterpret_cast<Vector*>(uintptr_t(this) + OFFSETS::m_aimPunchAngle);
		}
		bool GetImmunity()
		{
			return *reinterpret_cast<bool*>(uintptr_t(this) + OFFSETS::m_bGunGameImmunity);
		}
		bool SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
		{
			void* pRenderable = reinterpret_cast<void*>(uintptr_t(this) + 0x4);
			if (!pRenderable)
				false;

			typedef bool(__thiscall* Fn)(void*, matrix3x4_t*, int, int, float);
			return VMT::VMTHookManager::GetFunction<Fn>(pRenderable, 13)(pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
		}
		bool SetupBones1(VMatrix *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
		{
			/*void* pRenderable = reinterpret_cast<void*>(uintptr_t(this) + 0x4);
			if (!pRenderable)
			false;

			typedef bool(__thiscall* Fn)(void*, matrix3x4_t*, int, int, float);
			return VMT::VMTHookManager::GetFunction<Fn>(pRenderable, 13)(pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);*/
			__asm
			{
				mov edi, this
				lea ecx, dword ptr ds : [edi + 0x4]
				mov edx, dword ptr ds : [ecx]
				push currentTime
				push boneMask
				push nMaxBones
				push pBoneToWorldOut
				call dword ptr ds : [edx + 0x34]
			}
		}
		void UpdateClientSideAnimation()
		{
			typedef void(__thiscall* original)(void*);
			VMT::VMTHookManager::GetFunction<original>(this, 218)(this);
		}
		float GetSpread()
		{
			typedef float(__thiscall* original)(void*);
			return VMT::VMTHookManager::GetFunction<original>(this, 439)(this);
		}
		float GetInaccuracy()
		{
			typedef float(__thiscall* oInaccuracy)(PVOID);
			return VMT::VMTHookManager::GetFunction<oInaccuracy>(this, 469)(this);
		}
		void SetAbsOrigin(Vector ArgOrigin)
		{
			using Fn = void(__thiscall*)(CBaseEntity*, const Vector &origin);
			static Fn func;

			if (!func)
				func = (Fn)(UTILS::FindPattern("client.dll", (PBYTE)"\x55\x8B\xEC\x83\xE4\xF8\x51\x53\x56\x57\x8B\xF1\xE8\x00\x00", "xxxxxxxxxxxxx??"));

			func(this, ArgOrigin);
		}
		Vector& GetAbsAngles()
		{
			typedef Vector& (__thiscall* OriginalFn)(void*);
			return ((OriginalFn)VMT::VMTHookManager::GetFunction<OriginalFn>(this, 11))(this);
		}
		void SetAbsAngles(Vector angles)
		{
			using Fn = void(__thiscall*)(CBaseEntity*, const Vector &angles);
			static Fn func;

			if (!func)
				func = (Fn)(UTILS::FindPattern("client.dll", (BYTE*)"\x55\x8B\xEC\x83\xE4\xF8\x83\xEC\x64\x53\x56\x57\x8B\xF1\xE8", "xxxxxxxxxxxxxxx"));

			func(this, angles);
		}
		float* GetPoseParamaters()
		{
			return reinterpret_cast<float*>(uintptr_t(this) + OFFSETS::m_flPoseParameter);
		}
		Vector GetRenderAngles()
		{
			return *(Vector*)((DWORD)this + 0x128);
		}
		void SetRenderAngles(Vector angles)
		{
			*(Vector*)((DWORD)this + 0x128) = angles;
		}
		int DrawModel(int flags, uint8_t alpha)
		{
			void* pRenderable = (void*)(this + 0x4);

			using fn = int(__thiscall*)(void*, int, uint8_t);
			return VMT::VMTHookManager::GetFunction< fn >(pRenderable, 9)(pRenderable, flags, alpha);
		}
		ClientClass* GetClientClass()
		{
			void* Networkable = (void*)(this + 0x8);
			typedef ClientClass*(__thiscall* OriginalFn)(void*);
			return VMT::VMTHookManager::GetFunction<OriginalFn>(Networkable, 2)(Networkable);
		}
		float GetNextAttack()
		{
			return *reinterpret_cast<float*>(uint32_t(this) + OFFSETS::m_flNextAttack);
		}
		int GetActiveWeaponIndex()
		{
			return *reinterpret_cast<int*>(uintptr_t(this) + OFFSETS::m_hActiveWeapon) & 0xFFF;
		}
		int GetArmor()
		{
			return *reinterpret_cast<int*>(uintptr_t(this) + OFFSETS::m_ArmorValue);
		}
		bool HasHelmet()
		{
			return *reinterpret_cast<bool*>(uintptr_t(this) + OFFSETS::m_bHasHelmet);
		}
		char* GetArmorName()
		{
			if (GetArmor() > 0)
			{
				if (HasHelmet())
					return "hk";
				else
					return "k";
			}
			else
				return " ";
		}
		bool HasC4()
		{
			int iBombIndex = *(int*)(*(DWORD*)(OFFSETS::dwPlayerResource) + OFFSETS::m_iPlayerC4);
			if (iBombIndex == this->GetIndex())
				return true;
			else
				return false;
		}
	};
}