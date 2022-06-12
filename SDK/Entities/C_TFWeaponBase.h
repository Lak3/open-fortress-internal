#pragma once

#include "C_BaseCombatWeapon.h"

//Types here might be wrong.
class C_TFWeaponBase : public C_BaseCombatWeapon
{
public:
	virtual						~C_TFWeaponBase() = 0;

	virtual void				FallInit(void) = 0;
	virtual int					GetWeaponID(void) const = 0;
	virtual int					GetDamageType() const = 0;
	virtual int					GetCustomDamageType() const = 0;
	virtual int					GetSlotOverride(void) const = 0;
	virtual int					GetPositionOverride(void) const = 0;
	virtual void				SetSlotOverride(int unk1) = 0;
	virtual void				SetPositionOderride(int unk1) = 0;
	virtual float				GetDamage(void) const = 0;
	virtual bool				CanSecondaryAttack(void) const = 0;
	virtual bool				CanDropManualy(void) const = 0; //Typo? -> C_TFWeaponBase::CanDropManualy(void)const
	virtual bool				DontAutoEquip(void) const = 0;
	virtual bool				LoadsManualy(void) const = 0; //Manually hard to write? -> C_TFWeaponBase::LoadsManualy(void)const
	virtual void				PlayWeaponShootSound(void) = 0;
	virtual bool				PrimaryAttackSwapsActivities(void) = 0;
	virtual bool				FiresInBursts(void) = 0;
	virtual bool				CalcIsAttackCriticalHelper(void) = 0;
	virtual void				DefaultReload(int a1, int a2, int a3) = 0;
	virtual bool				CanDrop(void) = 0;
	virtual bool				CanSoftZoom(void) = 0;
	virtual bool				SoftZoomCheck(void) = 0;
	virtual bool				IsLowered(void) = 0;
	virtual bool				InBarrage(void) = 0;
	virtual float				GetBurstTotalTime(void) = 0;
	virtual void				WeaponReset(void) = 0;
	virtual const char*			GetMuzzleFlashEffectName_3rd(void) = 0;
	virtual const char*			GetMuzzleFlashEffectName_1st(void) = 0;
	virtual const char*			GetMuzzleFlashModel(void) = 0;
	virtual float				GetMuzzleFlashLifetime(void) = 0;
	virtual const char*			GetMuzzleFlashParticleEffect(void) = 0;
	virtual float				GetWindupTime(void) = 0;
	virtual void				Operator_HandleAnimEvent(void* a1, C_BaseCombatCharacter* a2) = 0;
	virtual bool				CanFireCiritcalShot(bool a1) = 0;
	virtual float				GetProjectileSpeed(void) = 0;
	virtual void				CreateMuzzleFlasheffects(C_BaseEntity* a1, int a2) = 0;

public:
	inline bool CanPrimaryAttack(C_BasePlayer* pOwner)
	{
		if (pOwner)
		{
			const float flCurTime = TICKS_TO_TIME(pOwner->m_nTickBase());
			return ((m_flNextPrimaryAttack() <= flCurTime) && (pOwner->m_flNextAttack() <= flCurTime));
		}

		return false;
	}

public:
	NETVAR(m_bLowered, bool, "CTFWeaponBase", "m_bLowered");
	NETVAR(m_iReloadMode, int, "CTFWeaponBase", "m_iReloadMode");
	NETVAR(m_bResetParity, bool, "CTFWeaponBase", "m_bResetParity");
	NETVAR(m_bReloadedThroughAnimEvent, bool, "CTFWeaponBase", "m_bReloadedThroughAnimEvent");
	NETVAR(m_bInBarrage, bool, "CTFWeaponBase", "m_bInBarrage");
	NETVAR(m_bWindingUp, bool, "CTFWeaponBase", "m_bWindingUp");
	NETVAR(m_bSwapFire, bool, "CTFWeaponBase", "m_bSwapFire");
	NETVAR(m_flWindTick, float, "CTFWeaponBase", "m_flWindTick");
	NETVAR(m_iDamageIncrease, int, "CTFWeaponBase", "m_iDamageIncrease");
	NETVAR(m_iSlotOverride, int, "CTFWeaponBase", "m_iSlotOverride");
	NETVAR(m_iPositionOverride, int, "CTFWeaponBase", "m_iPositionOverride");
	NETVAR(m_flBlastRadiusIncrease, float, "CTFWeaponBase", "m_flBlastRadiusIncrease");
	NETVAR(m_flDamageBuildup, float, "CTFWeaponBase", "m_flDamageBuildup");
	NETVAR(m_flNextShotTime, float, "CTFWeaponBase", "m_flNextShotTime");
	NETVAR(m_iShotsDue, int, "CTFWeaponBase", "m_iShotsDue");
};

class C_TFMinigun : public C_TFWeaponBase
{
public:
	NETVAR(m_iWeaponState, int, "CTFMinigun", "m_iWeaponState");
	NETVAR(m_bCritShot, bool, "CTFMinigun", "m_bCritShot");
};