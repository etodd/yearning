#pragma once

#define RELEASE_BUILD 1

#define MAX_PLAYERS 12

#define MAX_GAMEPADS 4

#define MAX_MINIONS 96

#define MAX_ANIMATIONS 4

#define MAX_RESPAWNS 1000
#define MAX_ENERGY_LIMIT 30000

// if you change this, make sure to allocate more physics categories for each team's force field
#define MAX_TEAMS 4

#define GAME_VERSION 38

#define STEAM_APP_ID 728100
#define DISCORD_APP_ID "367724608469860353"

#define MAX_USERNAME 79

#define MAX_BONES 72

#define MAX_AUDIO_EVENT_NAME 63

#define VOLUME_MULTIPLIER 0.01f

#define AFK_TIME 120.0f
#define UI_JOYSTICK_DEAD_ZONE 0.5f
#define MAX_ABILITIES 2
#define MAX_START_ENERGY 1000
#define COOLDOWN_SPEED_MAX_INDEX (4 * 3)

#define MAX_BONE_WEIGHTS 4

#define MAX_CHAT 128
#define NET_MASTER_PORT 3497
#define NET_MASTER_HTTP_PORT 3498
#define NET_OAUTH_PORT 3499
#define NET_SYNC_TOLERANCE_POS 0.2f
#define NET_SYNC_TOLERANCE_ROT 0.2f
#define NET_MAX_PACKET_SIZE 4000
#define NET_SEQUENCE_COUNT 1023
#define NET_SEQUENCE_INVALID NET_SEQUENCE_COUNT
#define NET_ACK_PREVIOUS_SEQUENCES 64
#define NET_MAX_SEQUENCE_GAP 180
#define NET_PREVIOUS_SEQUENCES_SEARCH NET_MAX_SEQUENCE_GAP
#define NET_TIMEOUT (256.0f * (1.0f / 60.0f))
#define NET_MAX_MESSAGES_SIZE 1000
#define NET_SEQUENCE_RESEND_BUFFER NET_ACK_PREVIOUS_SEQUENCES
#define NET_HISTORY_SIZE 256
#define NET_MASTER_STATUS_INTERVAL 1.0f
#define NET_SERVER_IDLE_TIME 5.0f
#define NET_MAX_RTT_COMPENSATION 0.2f

#define LEVEL_ALLOWED(x) (true)

#define MAX_REVERBS 3

#define MAX_ZONES 64

#define MAX_ENTITIES 2048

#define TRANSITION_TIME 1.0f // time to transition between levels / overworld

#define PVP_ACCESSIBLE Vec4(0.7f, 0.7f, 0.7f, 1.0f)
#define PVP_ACCESSIBLE_NO_OVERRIDE Vec4(0.7f, 0.7f, 0.7f, MATERIAL_NO_OVERRIDE)
#define PVP_INACCESSIBLE Vec4(0.0f, 0.0f, 0.0f, MATERIAL_NO_OVERRIDE)

#define SCORE_SUMMARY_DELAY 2.0f
#define SCORE_SUMMARY_ACCEPT_DELAY 3.0f
#define SCORE_SUMMARY_ACCEPT_TIME (SCORE_SUMMARY_DELAY + 45.0f)

#define ZONE_UNDER_ATTACK_TIME 90.0f
#define ZONE_UNDER_ATTACK_THRESHOLD 15.0f

#define MAX_PATH_LENGTH 1024
#define MAX_AUTH_KEY 1024
#define AI_MAX_PATH_LENGTH 64

#define ROPE_SEGMENT_LENGTH 1.0f
#define ROPE_RADIUS 0.075f

#define ENERGY_INITIAL 0
#define ENERGY_MINION_KILL 10
#define ENERGY_RECTIFIER_DESTROY 20
#define ENERGY_FORCE_FIELD_DESTROY 10
#define ENERGY_GRENADE_DESTROY 10
#define ENERGY_DRONE_DESTROY 5
#define ENERGY_DRONE_DAMAGE 15
#define ENERGY_DIE 40
#define ENERGY_TURRET_DESTROY 20
#define ENERGY_MINION_SPAWNER_DESTROY 15

#define SPAWN_EFFECT_LIFETIME 1.5f
#define UPGRADE_STATION_RADIUS 0.5f

#define UPGRADE_TIME 1.5f
#define TEAM_SELECT_TIME 30.0f

#define ACTIVE_ARMOR_TIME 1.5f

#define DRONE_FLY_SPEED 30.0f
#define DRONE_CRAWL_SPEED 3.5f
#define DRONE_DASH_SPEED 20.0f
#define DRONE_DASH_TIME 0.35f
#define DRONE_DASH_DISTANCE (DRONE_DASH_SPEED * DRONE_DASH_TIME)
#define DRONE_MAX_DISTANCE 20.0f
#define DRONE_RADIUS 0.2f
#define DRONE_VERTICAL_DOT_LIMIT 0.9998f
#define DRONE_VERTICAL_ANGLE_LIMIT ((PI * 0.5f) - 0.021f)

#define DRONE_HEALTH 1
#define DRONE_SHIELD_AMOUNT 2
#define DRONE_SHIELD_MAX 20
#define SHIELD_REGEN_DELAY 6.0f
#define SHIELD_REGEN_TIME 3.0f
#define DRONE_COOLDOWN_ABILITY_SWITCH_MAX 1.0f
#define DRONE_COOLDOWN_THRESHOLD 1.0f
#define DRONE_COOLDOWN_MAX 3.0f
#define DRONE_COOLDOWN_THRESHOLD_TIME 1.25f
#define DRONE_COOLDOWN_SPEED (Game::session.config.ruleset.cooldown_speed() * (DRONE_COOLDOWN_THRESHOLD / DRONE_COOLDOWN_THRESHOLD_TIME))
#define DRONE_LEGS 3
#define DRONE_SNIPE_DISTANCE 100.0f
#define DRONE_THIRD_PERSON_OFFSET 2.0f
#define DRONE_SHIELD_RADIUS 0.6f
#define DRONE_OVERSHIELD_RADIUS (DRONE_SHIELD_RADIUS * 1.667f)
#define DRONE_CAMERA_SMOOTH_TIME 1.0f

#define MINION_SPAWNER_RADIUS 0.3f
#define MINION_SPAWNER_HEALTH 6

#define TURRET_HEALTH 12
#define TURRET_RADIUS 0.5f
#define TURRET_RANGE (DRONE_MAX_DISTANCE - TURRET_RADIUS - DRONE_SHIELD_RADIUS)
#define TURRET_COOLDOWN 1.5f

#define FLAG_RESTORE_TIME 20.0f
#define FLAG_RADIUS 0.2f

#define MINION_HEAD_RADIUS 0.4f
#define MINION_ATTACK_TIME 1.9f
#define MINION_HEARING_RANGE 8.0f
#define MINION_VISION_RANGE (DRONE_MAX_DISTANCE * 0.8f)
#define MINION_MELEE_RANGE 2.5f
#define MINION_HEALTH 6

#define RECTIFIER_HEAL_INTERVAL 0.8f
#define RECTIFIER_HEAL_AMOUNT 1
#define RECTIFIER_HEAL_MAX_CONCURRENT 4
#define RECTIFIER_RANGE 11.0f
#define RECTIFIER_RADIUS 0.2f
#define RECTIFIER_HEALTH 9

#define BATTERY_HEALTH 6
#define BATTERY_ENERGY_INCREMENT 24
#define BATTERY_ENERGY (BATTERY_ENERGY_INCREMENT * 10)
#define BATTERY_ENERGY_INCREMENT_TIME 6.0f
#define BATTERY_SPAWN_DELAY 10.0f
#define BATTERY_TIME_REWARD (BATTERY_SPAWN_DELAY + 135.0f)

#define DEFAULT_ASSAULT_TIME_LIMIT_MINUTES 6

#define FORCE_FIELD_HEALTH_NERFED 40
#define FORCE_FIELD_HEALTH_NORMAL 60
#define FORCE_FIELD_HEALTH_BUFFED 80
#define FORCE_FIELD_RADIUS 8.0f
#define FORCE_FIELD_BASE_OFFSET 0.95f

#define GRENADE_HEALTH 2
#define GRENADE_LAUNCH_SPEED 20.0f
#define GRENADE_RADIUS 0.125f
#define GRENADE_RANGE 13.0f
#define GRENADE_DELAY 2.0f
#define GRENADE_QUICK_FUSE 0.3f

#define MINION_SPAWN_HEIGHT 0.5f

#define BOLT_SPEED_MINION 12.0f
#define BOLT_SPEED_TURRET 12.0f
#define BOLT_SPEED_DRONE_BOLTER 25.0f
#define BOLT_SPEED_DRONE_SHOTGUN 40.0f
#define BOLT_LENGTH 0.5f
#define BOLT_LIGHT_RADIUS 10.0f
#define BOLTER_INTERVAL 0.125f

#define BATTERY_RADIUS 0.55f

#define AIR_CONTROL_ACCEL 5.0f
