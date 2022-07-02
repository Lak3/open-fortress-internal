#pragma once

#include "C_BaseSchemaEntity.h"

class CHudTexture;
class FileWeaponInfo_t;

#define MAX_SHOOT_SOUNDS 16
#define MAX_WEAPON_STRING 80
#define MAX_WEAPON_PREFIX 16
#define MAX_WEAPON_AMMO_NAME 32

class C_BaseCombatWeapon : public C_BaseSchemaEntity
{
public:
	virtual						~C_BaseCombatWeapon() = 0;

	virtual bool				IsPredicted(void) const = 0;
	virtual void				OnLoadWeaponScript(void) = 0;
	virtual void				SetupSchemaItem(const char* unk1) = 0;
	virtual int					GetSubType(void) = 0;
	virtual void				SetSubType(int iType) = 0;
	virtual void				Equip(C_BaseCombatCharacter* pOwner) = 0;
	virtual void				Drop(const Vector& vecVelocity) = 0;
	virtual	int					UpdateClientData(C_BaseEntity* pPlayer) = 0;
	virtual bool				IsAllowedToSwitch(void) = 0;
	virtual bool				CanBeSelected(void) = 0;
	virtual bool				VisibleInWeaponSelection(void) = 0;
	virtual bool				HasAmmo(void) = 0;
	virtual void				SetPickupTouch(void) = 0;
	virtual void 				DefaultTouch(C_BaseEntity* pOther) = 0;
	virtual void				GiveTo(C_BaseEntity* pOther) = 0;
	virtual bool				ShouldDisplayAltFireHUDHint() = 0;
	virtual void				DisplayAltFireHudHint() = 0;
	virtual void				RescindAltFireHudHint() = 0;
	virtual bool				ShouldDisplayReloadHUDHint() = 0;
	virtual void				DisplayReloadHudHint() = 0;
	virtual void				RescindReloadHudHint() = 0;
	virtual void				SetViewModelIndex(int index = 0) = 0;
	virtual bool				SendWeaponAnim(int iActivity) = 0;
	virtual void				SendViewModelAnim(int nSequence) = 0;
	virtual void				SetViewModel() = 0;
	virtual bool				HasWeaponIdleTimeElapsed(void) = 0;
	virtual void				SetWeaponIdleTime(float time) = 0;
	virtual float				GetWeaponIdleTime(void) = 0;
	virtual bool				HasAnyAmmo(void) = 0;
	virtual bool				HasPrimaryAmmo(void) = 0;
	virtual bool				HasSecondaryAmmo(void) = 0;
	virtual bool				CanHolster(void) = 0;
	virtual bool				DefaultDeploy(char* szViewModel, char* szWeaponModel, int iActivity, char* szAnimExt) = 0;
	virtual bool				CanDeploy(void) = 0;
	virtual bool				Deploy(void) = 0;
	virtual bool				Holster(C_BaseCombatWeapon* pSwitchingTo = NULL) = 0;
	virtual C_BaseCombatWeapon* GetLastWeapon(void) = 0;
	virtual void				SetWeaponVisible(bool visible) = 0;
	virtual bool				IsWeaponVisible(void) = 0;
	virtual bool				ReloadOrSwitchWeapons(void) = 0;
	virtual void				OnActiveStateChanged(int iOldState) = 0;
	virtual bool				HolsterOnDetach() = 0;
	virtual bool				IsHolstered() = 0;
	virtual void				Detach() = 0;
	virtual void				ItemPreFrame(void) = 0;
	virtual void				ItemPostFrame(void) = 0;
	virtual void				ItemBusyFrame(void) = 0;
	virtual void				ItemHolsterFrame(void) = 0;
	virtual void				WeaponIdle(void) = 0;
	virtual void				HandleFireOnEmpty() = 0;
	virtual bool				CanPerformSecondaryAttack(void)const = 0;
	virtual bool				ShouldBlockPrimaryFire() = 0;
	virtual void				CreateMove(float flInputSampleTime, CUserCmd* pCmd, const Vector& vecOldViewAngles) = 0;
	virtual bool				IsWeaponZoomed() = 0;
	virtual	void				CheckReload(void) = 0;
	virtual void				FinishReload(void) = 0;
	virtual void				AbortReload(void) = 0;
	virtual bool				Reload(void) = 0;
	virtual void				PrimaryAttack(void) = 0;
	virtual void				SecondaryAttack(void) = 0;
	virtual int					GetPrimaryAttackActivity(void) = 0;
	virtual int					GetSecondaryAttackActivity(void) = 0;
	virtual int					GetDrawActivity(void) = 0;
	virtual float				GetDefaultAnimSpeed(void) = 0;
	virtual int					GetBulletType(void) = 0;
	virtual const Vector&		GetBulletSpread(void) = 0;
	virtual Vector				GetBulletSpread(int proficiency) = 0;
	virtual float				GetSpreadBias(int proficiency) = 0;
	virtual float				GetFireRate(void) = 0;
	virtual int					GetMinBurst() = 0;
	virtual int					GetMaxBurst() = 0;
	virtual float				GetMinRestTime() = 0;
	virtual float				GetMaxRestTime() = 0;
	virtual int					GetRandomBurst() = 0;
	virtual void				WeaponSound(int sound_type, float soundtime = 0.0f) = 0;
	virtual void				StopWeaponSound(int sound_type) = 0;
	virtual const void*			GetProficiencyValues() = 0;
	virtual float				GetMaxAutoAimDeflection() = 0;
	virtual float				WeaponAutoAimScale() = 0;
	virtual bool				StartSprinting(void) = 0;
	virtual bool				StopSprinting(void) = 0;
	virtual float				GetDamage(float flDistance, int iLocation) = 0;
	virtual void				SetActivity(int act, float duration) = 0;
	virtual void				AddViewKick(void) = 0;
	virtual char*				GetDeathNoticeName(void) = 0;
	virtual void				SetOwner(C_BaseCombatCharacter* owner) = 0;
	virtual void				OnPickedUp(C_BaseCombatCharacter* pNewOwner) = 0;
	virtual void				AddViewmodelBob(C_BaseViewModel* viewmodel, Vector& origin, Vector& angles) = 0;
	virtual float				CalcViewmodelBob(void) = 0;
	virtual void 				GetControlPanelInfo(int nPanelIndex, const char*& pPanelName) = 0;
	virtual void				GetControlPanelClassName(int nPanelIndex, const char*& pPanelName) = 0;
	virtual bool				ShouldShowControlPanels(void) = 0;
	virtual bool				CanBePickedUpByNPCs(void) = 0;
	virtual int					GetSkinOverride() const = 0;
	virtual const char*			GetViewModel(int viewmodelindex = 0) const = 0;
	virtual const char*			GetWorldModel(void) const = 0;
	virtual const char*			GetAnimPrefix(void) const = 0;
	virtual int					GetMaxClip1(void) const = 0;
	virtual int					GetMaxClip2(void) const = 0;
	virtual int					GetDefaultClip1(void) const = 0;
	virtual int					GetDefaultClip2(void) const = 0;
	virtual int					GetMaxReserveAmmo(void) const = 0;
	virtual int					GetDefaultReserveAmmo(void) const = 0;
	virtual int					GetWeight(void) const = 0;
	virtual bool				AllowsAutoSwitchTo(void) const = 0;
	virtual bool				AllowsAutoSwitchFrom(void) const = 0;
	virtual bool				ForceWeaponSwitch(void) const = 0;
	virtual int					GetWeaponFlags(void) const = 0;
	virtual int					GetSlot(void) const = 0;
	virtual int					GetPosition(void) const = 0;
	virtual char const*			GetName(void) const = 0;
	virtual char const*			GetPrintName(void) const = 0;
	virtual char const*			GetShootSound(int iIndex) const = 0;
	virtual int					GetRumbleEffect() const = 0;
	virtual bool				UsesClipsForAmmo1(void) const = 0;
	virtual bool				UsesClipsForAmmo2(void) const = 0;
	virtual const unsigned char* GetEncryptionKey(void) = 0;
	virtual int					GetPrimaryAmmoType(void) const = 0;
	virtual int					GetSecondaryAmmoType(void) const = 0;
	virtual int					Clip1() = 0;
	virtual int					Clip2() = 0;
	virtual int					ReserveAmmo(void) = 0;
	virtual int					DefaultReserveAmmo(void) = 0;
	virtual CHudTexture const*	GetSpriteIconBlue(void) const = 0;
	virtual CHudTexture const*	GetSpriteIconRed(void) const = 0;
	virtual CHudTexture const*	GetSpriteIconCustom(void) const = 0;
	virtual CHudTexture const*	GetSpriteAmmo(void) const = 0;
	virtual CHudTexture const*	GetSpriteAmmo2(void) const = 0;
	virtual CHudTexture const*	GetSpriteCrosshair(void) const = 0;
	virtual CHudTexture const*	GetSpriteAutoaim(void) const = 0;
	virtual CHudTexture const*	GetSpriteZoomedCrosshair(void) const = 0;
	virtual CHudTexture const*	GetSpriteZoomedAutoaim(void) const = 0;
	virtual int					ActivityOverride(int baseAct, bool* pRequired) = 0;
	virtual	void*				ActivityList(void) = 0;
	virtual void				PoseParameterOverride(bool unk1) = 0;
	virtual void				PoseParamList(int& unk1) = 0;
	virtual bool				ShouldUseLargeViewModelVROverride(void) = 0;
	virtual bool				OnFireEvent(C_BaseViewModel* pViewModel, const Vector& origin, const Vector& angles, int event, const char* options) = 0;
	virtual void				RestartParticleEffect(void) = 0;
	virtual void				Redraw(void) = 0;
	virtual void				ViewModelDrawn(C_BaseViewModel* pViewModel) = 0;
	virtual void				DrawCrosshair(void) = 0;
	virtual bool				ShouldDrawCrosshair(void) = 0;
	virtual bool				IsCarriedByLocalPlayer(void) = 0;
	virtual bool				ShouldDrawUsingViewModel(void) = 0;
	virtual bool				IsActiveByLocalPlayer(void) = 0;
	virtual bool				ShouldDrawPickup(void) = 0;
	virtual void				HandleInput(void) = 0;
	virtual void				OverrideMouseInput(float* x, float* y) = 0;
	virtual int					KeyInput(int down, ButtonCode_t keynum, const char* pszCurrentBinding) = 0;
	virtual bool				AddLookShift(void) = 0;
	virtual void				GetViewmodelBoneControllers(C_BaseViewModel* pViewModel, float controllers[MAXSTUDIOBONECTRLS]) = 0;
	virtual int					GetWorldModelIndex(void) = 0;
	virtual void				GetWeaponCrosshairScale(float& flScale) = 0;
	virtual bool				ViewModel_IsTransparent(void) = 0;
	virtual bool				ViewModel_IsUsingFBTexture(void) = 0;
	virtual bool				IsOverridingViewmodel(void) = 0;
	virtual int					DrawOverriddenViewmodel(C_BaseViewModel* pViewmodel, int flags) = 0;
	virtual bool				CanLower(void) = 0;
	virtual bool				Ready(void) = 0;
	virtual bool				Lower(void) = 0;
	virtual void				HideThink(void) = 0;
	virtual bool				CanReload(void) = 0;

private:
	virtual void*				NetworkStateChanged_m_nNextThinkTick(void) = 0;
	virtual void*				NetworkStateChanged_m_nNextThinkTick(void* unk1) = 0;

public:
	inline const FileWeaponInfo_t& GetWpnData() {
		return reinterpret_cast<const FileWeaponInfo_t & (__thiscall*)(void*)>(U::Offsets.m_dwC_BaseCombatWeapon_GetWpnData)(this);
	}

public:
	NETVAR(m_iClip1, int, "CBaseCombatWeapon", "m_iClip1");
	NETVAR(m_iClip2, int, "CBaseCombatWeapon", "m_iClip2");
	NETVAR(m_iReserveAmmo, int, "CBaseCombatWeapon", "m_iReserveAmmo");
	NETVAR(m_iPrimaryAmmoType, int, "CBaseCombatWeapon", "m_iPrimaryAmmoType");
	NETVAR(m_iSecondaryAmmoType, int, "CBaseCombatWeapon", "m_iSecondaryAmmoType");
	NETVAR(m_nViewModelIndex, int, "CBaseCombatWeapon", "m_nViewModelIndex");
	NETVAR(m_bFlipViewModel, bool, "CBaseCombatWeapon", "m_bFlipViewModel");
	NETVAR(m_flNextPrimaryAttack, float, "CBaseCombatWeapon", "m_flNextPrimaryAttack");
	NETVAR(m_flNextSecondaryAttack, float, "CBaseCombatWeapon", "m_flNextSecondaryAttack");
	NETVAR(m_nNextThinkTick, int, "CBaseCombatWeapon", "m_nNextThinkTick");
	NETVAR(m_flTimeWeaponIdle, float, "CBaseCombatWeapon", "m_flTimeWeaponIdle");
	NETVAR(m_iViewModelIndex, int, "CBaseCombatWeapon", "m_iViewModelIndex");
	NETVAR(m_iWorldModelIndex, int, "CBaseCombatWeapon", "m_iWorldModelIndex");
	NETVAR(m_iState, int, "CBaseCombatWeapon", "m_iState");
	NETVAR(m_hOwner, int, "CBaseCombatWeapon", "m_hOwner");
};

//TODO: Untested, verify the integrity of this.
class FileWeaponInfo_t
{
public:
	virtual void Parse(KeyValues* pKeyValuesData, const char* szWeaponName) = 0;

public:
	bool					bParsedScript;
	bool					bLoadedHudElements;
	char					szClassName[MAX_WEAPON_STRING];
	char					szPrintName[MAX_WEAPON_STRING];			// Name for showing in HUD, etc.
	char					szViewModel[MAX_WEAPON_STRING];			// View model of this weapon
	char					szWorldModel[MAX_WEAPON_STRING];		// Model of this weapon seen carried by the player
	char					szAnimationPrefix[MAX_WEAPON_PREFIX];	// Prefix of the animations that should be used by the player carrying this weapon
	int						iSlot;									// inventory slot.
	int						iPosition;								// position in the inventory slot.
	int						iMaxClip1;								// max primary clip size (-1 if no clip)
	int						iMaxClip2;								// max secondary clip size (-1 if no clip)
	int						iDefaultClip1;							// amount of primary ammo in the gun when it's created
	int						iDefaultClip2;							// amount of secondary ammo in the gun when it's created
	int						iWeight;								// this value used to determine this weapon's importance in autoselection.
	int						iRumbleEffect;							// Which rumble effect to use when fired? (xbox)
	bool					bAutoSwitchTo;							// whether this weapon should be considered for autoswitching to
	bool					bAutoSwitchFrom;						// whether this weapon can be autoswitched away from when picking up another weapon or ammo
	int						iFlags;									// miscellaneous weapon flags
	char					szAmmo1[MAX_WEAPON_AMMO_NAME];			// "primary" ammo type
	char					szAmmo2[MAX_WEAPON_AMMO_NAME];			// "secondary" ammo type
	char					aShootSounds[NUM_SHOOT_SOUND_TYPES][MAX_WEAPON_STRING];
	int						iAmmoType;
	int						iAmmo2Type;
	bool					m_bMeleeWeapon;
	bool					m_bBuiltRightHanded;
	bool					m_bAllowFlipping;
	int						iSpriteCount;
	CHudTexture*            iconActive;
	CHudTexture*			iconInactive;
	CHudTexture*			iconAmmo;
	CHudTexture*			iconAmmo2;
	CHudTexture*			iconCrosshair;
	CHudTexture*			iconAutoaim;
	CHudTexture*			iconZoomedCrosshair;
	CHudTexture*			iconZoomedAutoaim;
	CHudTexture*			iconSmall;
	bool					bShowUsageHint;
};