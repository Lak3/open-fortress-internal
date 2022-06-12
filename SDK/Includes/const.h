#pragma once

#include "../../Util/Util.h"

#define MAX_PLAYERS 33

#define STEAM_PARM "-steam"
#define AUTO_RESTART "-autoupdate"
#define INVALID_STEAM_TICKET "Invalid STEAM UserID Ticket\n"
#define INVALID_STEAM_VACBANSTATE "VAC banned from secure server\n"
#define INVALID_STEAM_LOGGED_IN_ELSEWHERE "This Steam account is being used in another location\n"
#define INVALID_STEAM_LOGON_NOT_CONNECTED "Client not connected to Steam\n"
#define INVALID_STEAM_LOGON_TICKET_CANCELED "Client left game (Steam auth ticket has been canceled)\n"
#define CLIENTNAME_TIMED_OUT "%s timed out"

#define DEFAULT_TICK_INTERVAL (0.015)
#define MINIMUM_TICK_INTERVAL (0.001)
#define MAXIMUM_TICK_INTERVAL (0.1)
#define ABSOLUTE_PLAYER_LIMIT 255
#define ABSOLUTE_PLAYER_LIMIT_DW ((ABSOLUTE_PLAYER_LIMIT/32) + 1)
#define MAX_PLAYER_NAME_LENGTH 32
#define MAX_PLAYERS_PER_CLIENT 1
#define MAX_MAP_NAME 96
#define MAX_MAP_NAME_SAVE 32
#define MAX_DISPLAY_MAP_NAME 32
#define	MAX_NETWORKID_LENGTH 64
#define SP_MODEL_INDEX_BITS 13
#define	MAX_EDICT_BITS 11
#define	MAX_EDICTS (1<<MAX_EDICT_BITS)
#define MAX_SERVER_CLASS_BITS 9
#define MAX_SERVER_CLASSES (1<<MAX_SERVER_CLASS_BITS)
#define SIGNED_GUID_LEN 32
#define NUM_ENT_ENTRY_BITS (MAX_EDICT_BITS + 1)
#define NUM_ENT_ENTRIES (1 << NUM_ENT_ENTRY_BITS)
#define ENT_ENTRY_MASK (NUM_ENT_ENTRIES - 1)
#define INVALID_EHANDLE_INDEX 0xFFFFFFFF
#define NUM_SERIAL_NUM_BITS (32 - NUM_ENT_ENTRY_BITS)
#define NUM_NETWORKED_EHANDLE_SERIAL_NUMBER_BITS 10
#define NUM_NETWORKED_EHANDLE_BITS (MAX_EDICT_BITS + NUM_NETWORKED_EHANDLE_SERIAL_NUMBER_BITS)
#define INVALID_NETWORKED_EHANDLE_VALUE ((1 << NUM_NETWORKED_EHANDLE_BITS) - 1)
#define MAX_PACKEDENTITY_DATA (16384)
#define MAX_PACKEDENTITY_PROPS (4096)
#define MAX_CUSTOM_FILES 4
#define MAX_CUSTOM_FILE_SIZE 524288

#define	FL_ONGROUND (1<<0)
#define FL_DUCKING (1<<1)
#define	FL_WATERJUMP (1<<2)
#define FL_ONTRAIN (1<<3)
#define FL_INRAIN (1<<4)
#define FL_FROZEN (1<<5)
#define FL_ATCONTROLS (1<<6)
#define	FL_CLIENT (1<<7)
#define FL_FAKECLIENT (1<<8)
#define	FL_INWATER (1<<9)
#define PLAYER_FLAG_BITS 10

enum MoveType_t
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4
};

enum MoveCollide_t
{
	MOVECOLLIDE_DEFAULT = 0,
	MOVECOLLIDE_FLY_BOUNCE,
	MOVECOLLIDE_FLY_CUSTOM,
	MOVECOLLIDE_FLY_SLIDE,
	MOVECOLLIDE_COUNT,
	MOVECOLLIDE_MAX_BITS = 3
};

enum SolidType_t
{
	SOLID_NONE = 0,
	SOLID_BSP = 1,
	SOLID_BBOX = 2,
	SOLID_OBB = 3,
	SOLID_OBB_YAW = 4,
	SOLID_CUSTOM = 5,
	SOLID_VPHYSICS = 6,
	SOLID_LAST
};

enum SolidFlags_t
{
	FSOLID_CUSTOMRAYTEST = 0x0001,
	FSOLID_CUSTOMBOXTEST = 0x0002,
	FSOLID_NOT_SOLID = 0x0004,
	FSOLID_TRIGGER = 0x0008,
	FSOLID_NOT_STANDABLE = 0x0010,
	FSOLID_VOLUME_CONTENTS = 0x0020,
	FSOLID_FORCE_WORLD_ALIGNED = 0x0040,
	FSOLID_USE_TRIGGER_BOUNDS = 0x0080,
	FSOLID_ROOT_PARENT_ALIGNED = 0x0100,
	FSOLID_TRIGGER_TOUCH_DEBRIS = 0x0200,
	FSOLID_MAX_BITS = 10
};

inline bool IsSolid(SolidType_t solidType, int nSolidFlags)
{
	return (solidType != SOLID_NONE) && ((nSolidFlags & FSOLID_NOT_SOLID) == 0);
}

#define	LIFE_ALIVE 0
#define	LIFE_DYING 1
#define	LIFE_DEAD 2
#define LIFE_RESPAWNABLE 3
#define LIFE_DISCARDBODY 4

enum
{
	EF_BONEMERGE = 0x001,
	EF_BRIGHTLIGHT = 0x002,
	EF_DIMLIGHT = 0x004,
	EF_NOINTERP = 0x008,
	EF_NOSHADOW = 0x010,
	EF_NODRAW = 0x020,
	EF_NORECEIVESHADOW = 0x040,
	EF_BONEMERGE_FASTCULL = 0x080,
	EF_ITEM_BLINK = 0x100,
	EF_PARENT_ANIMATES = 0x200,
	EF_MAX_BITS = 10
};

#define EF_PARITY_BITS 3
#define EF_PARITY_MASK ((1<<EF_PARITY_BITS)-1)
#define EF_MUZZLEFLASH_BITS 2
#define	PLAT_LOW_TRIGGER 1
#define	SF_TRAIN_WAIT_RETRIGGER	1
#define SF_TRAIN_PASSABLE 8
#define FIXANGLE_NONE 0
#define FIXANGLE_ABSOLUTE 1
#define FIXANGLE_RELATIVE 2
#define BREAK_GLASS 0x01
#define BREAK_METAL 0x02
#define BREAK_FLESH 0x04
#define BREAK_WOOD 0x08
#define BREAK_SMOKE 0x10
#define BREAK_TRANS 0x20
#define BREAK_CONCRETE 0x40
#define BREAK_SLAVE 0x80
#define BOUNCE_GLASS BREAK_GLASS
#define	BOUNCE_METAL BREAK_METAL
#define BOUNCE_FLESH BREAK_FLESH
#define BOUNCE_WOOD	 BREAK_WOOD
#define BOUNCE_SHRAP 0x10
#define BOUNCE_SHELL 0x20
#define	BOUNCE_CONCRETE BREAK_CONCRETE
#define BOUNCE_SHOTSHELL 0x80
#define TE_BOUNCE_NULL 0
#define TE_BOUNCE_SHELL 1
#define TE_BOUNCE_SHOTSHELL	2

enum RenderMode_t
{
	kRenderNormal = 0,
	kRenderTransColor,
	kRenderTransTexture,
	kRenderGlow,
	kRenderTransAlpha,
	kRenderTransAdd,
	kRenderEnvironmental,
	kRenderTransAddFrameBlend,
	kRenderTransAlphaAdd,
	kRenderWorldGlow,
	kRenderNone,
	kRenderModeCount
};

enum RenderFx_t
{
	kRenderFxNone = 0,
	kRenderFxPulseSlow,
	kRenderFxPulseFast,
	kRenderFxPulseSlowWide,
	kRenderFxPulseFastWide,
	kRenderFxFadeSlow,
	kRenderFxFadeFast,
	kRenderFxSolidSlow,
	kRenderFxSolidFast,
	kRenderFxStrobeSlow,
	kRenderFxStrobeFast,
	kRenderFxStrobeFaster,
	kRenderFxFlickerSlow,
	kRenderFxFlickerFast,
	kRenderFxNoDissipation,
	kRenderFxDistort,
	kRenderFxHologram,
	kRenderFxExplode,
	kRenderFxGlowShell,
	kRenderFxClampMinScale,
	kRenderFxEnvRain,
	kRenderFxEnvSnow,
	kRenderFxSpotlight,
	kRenderFxRagdoll,
	kRenderFxPulseFastWider,
	kRenderFxMax
};

enum ETFHitboxes
{
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_LOWER_NECK,
	HITBOX_PELVIS,
	HITBOX_BODY,
	HITBOX_THORAX,
	HITBOX_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_MAX
};

enum MinigunState_t
{
	AC_STATE_IDLE = 0,
	AC_STATE_STARTFIRING,
	AC_STATE_FIRING,
	AC_STATE_SPINNING,
	AC_STATE_DRYFIRE
};

enum Collision_Group_t
{
	COLLISION_GROUP_NONE = 0,
	COLLISION_GROUP_DEBRIS,
	COLLISION_GROUP_DEBRIS_TRIGGER,
	COLLISION_GROUP_INTERACTIVE_DEBRIS,
	COLLISION_GROUP_INTERACTIVE,
	COLLISION_GROUP_PLAYER,
	COLLISION_GROUP_BREAKABLE_GLASS,
	COLLISION_GROUP_VEHICLE,
	COLLISION_GROUP_PLAYER_MOVEMENT,
	COLLISION_GROUP_NPC,
	COLLISION_GROUP_IN_VEHICLE,
	COLLISION_GROUP_WEAPON,
	COLLISION_GROUP_VEHICLE_CLIP,
	COLLISION_GROUP_PROJECTILE,
	COLLISION_GROUP_DOOR_BLOCKER,
	COLLISION_GROUP_PASSABLE_DOOR,
	COLLISION_GROUP_DISSOLVING,
	COLLISION_GROUP_PUSHAWAY,
	COLLISION_GROUP_NPC_ACTOR,
	COLLISION_GROUP_NPC_SCRIPTED,
	LAST_SHARED_COLLISION_GROUP
};

#define SOUND_NORMAL_CLIP_DIST	1000.0f
#define MAX_AREA_STATE_BYTES 32
#define MAX_AREA_PORTAL_STATE_BYTES 24
#define MAX_USER_MSG_DATA 255
#define MAX_ENTITY_MSG_DATA 255

#define STUDIO_NONE 0x00000000
#define STUDIO_RENDER 0x00000001
#define STUDIO_VIEWXFORMATTACHMENTS 0x00000002
#define STUDIO_DRAWTRANSLUCENTSUBMODELS 0x00000004
#define STUDIO_TWOPASS 0x00000008
#define STUDIO_STATIC_LIGHTING 0x00000010
#define STUDIO_WIREFRAME 0x00000020
#define STUDIO_ITEM_BLINK 0x00000040
#define STUDIO_NOSHADOWS 0x00000080
#define STUDIO_WIREFRAME_VCOLLIDE 0x00000100
#define STUDIO_NO_OVERRIDE_FOR_ATTACH 0x00000200
#define STUDIO_GENERATE_STATS 0x01000000
#define STUDIO_SSAODEPTHTEXTURE 0x08000000
#define STUDIO_SHADOWDEPTHTEXTURE 0x40000000
#define STUDIO_TRANSPARENCY 0x80000000

enum EClassIds
{
	CTFBaseRocket = 161,
	CTFWeaponBaseMelee = 253,
	CTFWeaponBaseGun = 252,
	CTFWeaponBaseGrenadeProj = 251,
	CTFWeaponBase = 250,
	CTFCWrench = 191,
	CTFWrench = 260,
	CTFCTranq = 189,
	CTFSyringeGun = 245,
	CSniperDot = 95,
	CTFCSniperRifle = 188,
	CTFRailgun = 233,
	CTFSniperRifle = 242,
	CTFCAssaultRifle = 170,
	CTFAssaultRifle = 158,
	CTFTommyGun = 247,
	CTFSMG_Mercenary = 241,
	CTFSMG = 240,
	CTFShovel = 239,
	CTFEternalShotgun = 195,
	CTFLeverAction = 214,
	CTFCShotgunDB = 186,
	CTFCShotgunSB = 187,
	CTFScatterGun = 237,
	CTFSuperShotgun = 244,
	CTFShotgun = 238,
	CTFBouncer = 168,
	CTFSuperRocketLauncher = 243,
	CTFOriginal = 221,
	CTFCIncendiaryCannon = 175,
	CTFCRPG = 185,
	CTFRocketLauncher = 236,
	CTFRevolver_Mercenary = 235,
	CTFRevolver = 234,
	CTFCRailPistol = 183,
	CTFPistol_Akimbo = 224,
	CTFPistol_Mercenary = 225,
	CTFPistol_Scout = 226,
	CTFPistol = 223,
	CTFCPipebombLauncher = 182,
	CTFDynamite = 194,
	CTFPipebombLauncher = 222,
	CTFWeaponPDA_Spy = 259,
	CTFWeaponPDA_Engineer_Destroy = 258,
	CTFWeaponPDA_Engineer_Build = 257,
	CTFWeaponPDA = 256,
	CTFCNailgunSuper = 180,
	CTFCNailgun = 179,
	CTFNailgun = 219,
	CTFCAssaultCannon = 169,
	CTFGatlingGun = 202,
	CTFMinigun = 217,
	CTFMedkit = 216,
	CWeaponMedigun = 265,
	CTFCombatKnife = 181,
	CTFCKnife = 176,
	CTFKnife = 212,
	CTFWeaponInvis = 255,
	CTFCGrenadeLauncher = 173,
	CTFGrenadeLauncher_Mercenary = 206,
	CTFGrenadeLauncher = 205,
	CTFGrenadePipebombProjectile = 208,
	CWeaponGrapple = 264,
	CTFFlameThrowerDM = 199,
	CTFCFlameThrower = 172,
	CTFFlameThrowerPyro = 200,
	CTFFlag = 198,
	CTFJuggernaught = 211,
	CTFClaws = 177,
	CTFBerserk = 163,
	CTFFists = 197,
	CTFFireAxe = 196,
	CTFLeadPipe = 213,
	CTFCUmbrella = 190,
	CTFCCrowbar = 171,
	CTFUmbrella = 248,
	CTFCrowbar = 184,
	CTFClub = 178,
	CTFBottle = 167,
	CTFBonesaw = 166,
	CTFBat = 162,
	CTFWeaponBuilder = 254,
	CTFProjectile_BouncyRocket = 229,
	CTFProjectile_Rocket = 230,
	CTFHandModel = 209,
	CTFViewModel = 249,
	CTFGrenadeMirvBomb = 207,
	CTFBaseProjectile = 160,
	CBaseObjectUpgrade = 10,
	CTFItem = 210,
	CTFGameRulesProxy = 201,
	CTETFParticleEffect = 154,
	CTETFExplosion = 153,
	CTETFBlood = 152,
	CTeleportVortex = 136,
	CCaptureFlagReturnIcon = 24,
	CCaptureFlag = 23,
	CTFTeam = 246,
	CTFPlayerResource = 228,
	CTFPlayer = 227,
	CTFRagdoll = 232,
	CTEPlayerAnimEvent = 141,
	CTFObjectiveResource = 220,
	CTFGlow = 203,
	CTEFireBullets = 129,
	CTFAmmoPack = 156,
	CObjectTeleporter = 70,
	CObjectSentrygun = 69,
	CTFProjectile_SentryRocket = 231,
	CObjectSapper = 68,
	CObjectDispenser = 67,
	CFuncRespawnRoomVisualizer = 57,
	CFuncRespawnRoom = 56,
	CCaptureZone = 25,
	CBaseObject = 9,
	CTestTraceline = 151,
	CTEWorldDecal = 155,
	CTESpriteSpray = 150,
	CTESprite = 149,
	CTESparks = 148,
	CTESmoke = 147,
	CTEShowLine = 145,
	CTEProjectedDecal = 143,
	CTEPlayerDecal = 142,
	CTEPhysicsProp = 140,
	CTEParticleSystem = 139,
	CTEMuzzleFlash = 138,
	CTELargeFunnel = 135,
	CTEKillPlayerAttachments = 134,
	CTEImpact = 133,
	CTEGlowSprite = 132,
	CTEShatterSurface = 144,
	CTEFootprintDecal = 131,
	CTEFizz = 130,
	CTEExplosion = 128,
	CTEEnergySplash = 127,
	CTEEffectDispatch = 126,
	CTEDynamicLight = 125,
	CTEDecal = 123,
	CTEClientProjectile = 122,
	CTEBubbleTrail = 121,
	CTEBubbles = 120,
	CTEBSPDecal = 119,
	CTEBreakModel = 118,
	CTEBloodStream = 117,
	CTEBloodSprite = 116,
	CTEBeamSpline = 115,
	CTEBeamRingPoint = 114,
	CTEBeamRing = 113,
	CTEBeamPoints = 112,
	CTEBeamLaser = 111,
	CTEBeamFollow = 110,
	CTEBeamEnts = 109,
	CTEBeamEntPoint = 108,
	CTEBaseBeam = 107,
	CTEArmorRicochet = 106,
	CTEMetalSparks = 137,
	CSteamJet = 100,
	CSmokeStack = 94,
	DustTrail = 269,
	CFireTrail = 44,
	SporeTrail = 275,
	SporeExplosion = 274,
	RocketTrail = 272,
	SmokeTrail = 273,
	CPropVehicleDriveable = 86,
	ParticleSmokeGrenade = 271,
	CParticleFire = 72,
	MovieExplosion = 270,
	CTEGaussExplosion = 0,
	CEnvQuadraticBeam = 38,
	CEmbers = 31,
	CEnvWind = 42,
	CPrecipitation = 85,
	CBaseTempEntity = 17,
	CTFGravityGauntlets = 204,
	CWeaponPhysCannon = 266,
	CTFLightningGun = 215,
	CTFChainsaw = 174,
	CTFBFG = 164,
	CTFBFGProjectile = 165,
	CBaseSchemaEntity = 15,
	CTFAnnouncerSystem = 157,
	COFDTriggerJump = 71,
	CTFDMMusicManager = 192,
	CTFMusicPlayer = 218,
	CTFDroppedPowerup = 193,
	CTFAutoHumanTeam = 159,
	CFuncFilterVisualizer = 51,
	CWeaponSpawner = 267,
	CCondPowerup = 28,
	CTeamplayRoundBasedRulesProxy = 103,
	CTeamRoundTimer = 104,
	CSpriteTrail = 99,
	CSpriteOriented = 98,
	CSprite = 97,
	CRagdollPropAttached = 89,
	CRagdollProp = 88,
	CPoseController = 84,
	CGameRulesProxy = 61,
	CInfoLadderDismount = 62,
	CFuncLadder = 52,
	CEnvDetailController = 35,
	CWorld = 268,
	CWaterLODControl = 263,
	CVoteController = 262,
	CVGuiScreen = 261,
	CPropJeep = 0,
	CPropVehicleChoreoGeneric = 0,
	CTesla = 146,
	CTeamTrainWatcher = 105,
	CBaseTeamObjectiveResource = 16,
	CTeam = 102,
	CSun = 101,
	CParticlePerformanceMonitor = 73,
	CSpotlightEnd = 96,
	CSlideshowDisplay = 93,
	CShadowControl = 92,
	CSceneEntity = 91,
	CRopeKeyframe = 90,
	CRagdollManager = 87,
	CPhysicsPropMultiplayer = 78,
	CPhysBoxMultiplayer = 76,
	CBasePropDoor = 14,
	CDynamicProp = 30,
	CPointCommentaryNode = 83,
	CPointCamera = 82,
	CPlayerResource = 81,
	CPlasma = 80,
	CPhysMagnet = 79,
	CPhysicsProp = 77,
	CPhysBox = 75,
	CParticleSystem = 74,
	CMaterialModifyControl = 66,
	CLightGlow = 65,
	CInfoOverlayAccessor = 64,
	CFuncTrackTrain = 60,
	CFuncSmokeVolume = 59,
	CFuncRotating = 58,
	CFuncReflectiveGlass = 55,
	CFuncOccluder = 54,
	CFuncMonitor = 53,
	CFunc_LOD = 48,
	CTEDust = 124,
	CFunc_Dust = 47,
	CFuncConveyor = 50,
	CBreakableSurface = 22,
	CFuncAreaPortalWindow = 49,
	CFish = 45,
	CEntityFlame = 33,
	CFireSmoke = 43,
	CEnvTonemapController = 41,
	CEnvScreenEffect = 39,
	CEnvScreenOverlay = 40,
	CEnvProjectedTexture = 37,
	CEnvParticleScript = 36,
	CFogController = 46,
	CEntityParticleTrail = 34,
	CEntityDissolve = 32,
	CDynamicLight = 29,
	CColorCorrectionVolume = 27,
	CColorCorrection = 26,
	CBreakableProp = 21,
	CBasePlayer = 12,
	CBaseFlex = 7,
	CBaseEntity = 6,
	CBaseDoor = 5,
	CBaseCombatCharacter = 3,
	CBaseAnimatingOverlay = 2,
	CBoneFollower = 20,
	CBaseAnimating = 1,
	CInfoLightingRelative = 63,
	CAI_BaseNPC = 0,
	CBeam = 19,
	CBaseViewModel = 18,
	CBaseProjectile = 13,
	CBaseParticleEntity = 11,
	CBaseGrenade = 8,
	CBaseCombatWeapon = 4
};

enum ETFWeaponID
{
	TF_WEAPON_NONE,
	TF_WEAPON_BAT,
	TF_WEAPON_BOTTLE,
	TF_WEAPON_FIREAXE,
	TF_WEAPON_CLUB,
	TF_WEAPON_CROWBAR,
	TF_WEAPON_KNIFE,
	TF_WEAPON_FISTS,
	TF_WEAPON_SHOVEL,
	TF_WEAPON_WRENCH,
	TF_WEAPON_BONESAW,
	TF_WEAPON_SHOTGUN,
	TF_WEAPON_SCATTERGUN,
	TF_WEAPON_SNIPERRIFLE,
	TF_WEAPON_MINIGUN,
	TF_WEAPON_SMG,
	TF_WEAPON_SYRINGEGUN_MEDIC,
	TF_WEAPON_TRANQ,
	TF_WEAPON_ROCKETLAUNCHER,
	TF_WEAPON_GRENADELAUNCHER,
	TF_WEAPON_PIPEBOMBLAUNCHER,
	TF_WEAPON_FLAMETHROWER,
	TF_WEAPON_PISTOL,
	TF_WEAPON_PISTOL_SCOUT,
	TF_WEAPON_REVOLVER,
	TF_WEAPON_NAILGUN,
	TF_WEAPON_PDA,
	TF_WEAPON_PDA_ENGINEER_BUILD,
	TF_WEAPON_PDA_ENGINEER_DESTROY,
	TF_WEAPON_PDA_SPY,
	TF_WEAPON_BUILDER,
	TF_WEAPON_MEDIGUN,
	TF_WEAPON_FLAMETHROWER_ROCKET,
	TF_WEAPON_SENTRY_BULLET,
	TF_WEAPON_SENTRY_ROCKET,
	TF_WEAPON_DISPENSER,
	TF_WEAPON_INVIS,
	TF_WEAPON_RAILGUN,
	TF_WEAPON_SUPERSHOTGUN,
	TF_WEAPON_ETERNALSHOTGUN,
	TF_WEAPON_PISTOL_MERCENARY,
	TF_WEAPON_REVOLVER_MERCENARY,
	TF_WEAPON_GATLINGGUN,
	TF_WEAPON_PISTOL_AKIMBO,
	TF_WEAPON_UMBRELLA,
	TF_WEAPON_SMG_MERCENARY,
	TF_WEAPON_TOMMYGUN,
	TF_WEAPON_GRENADELAUNCHER_MERCENARY,
	TF_WEAPON_ROCKETLAUNCHER_DM,
	TF_WEAPON_ASSAULTRIFLE,
	TF_WEAPON_C4,
	TF_WEAPON_BERSERK,
	TF_WEAPON_PHYSCANNON,
	TF_WEAPON_SUPER_ROCKETLAUNCHER,
	TF_WEAPON_CHAINSAW,
	TF_WEAPON_DYNAMITE_BUNDLE,
	TF_WEAPON_LIGHTNING_GUN,
	TF_WEAPON_GRAPPLE,
	TF_WEAPON_GIB,
	TF_WEAPON_CLAWS,
	TF_WEAPON_JUGGERNAUGHT,
	TF_WEAPON_COMBATKNIFE,
	TF_WEAPON_BOUNCER,
	TF_WEAPON_GRAVITY_GAUNTLETS,
	TF_WEAPON_LEVER_ACTION,
	TF_WEAPON_LEAD_PIPE,
	TF_WEAPON_FLAMETHROWER_PYRO,
	TF_WEAPON_GRENADE_DEMOMAN,
	TF_WEAPON_GRENADE_PIPEBOMB,
	TF_WEAPON_GRENADE_MIRV,
	TF_WEAPON_GRENADE_MIRVBOMB,
	TF_WEAPON_COUNT
};