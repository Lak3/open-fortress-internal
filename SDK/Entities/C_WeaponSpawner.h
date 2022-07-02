#pragma once

#include "C_TFWeaponBaseGun.h"

class C_WeaponSpawner : public C_BaseAnimating
{
public:
	virtual		 ~C_WeaponSpawner() = 0;
	virtual bool OwnsWeaponAkimbo(const char* a1, C_TFPlayer* a2) = 0;
	virtual bool OwnsWeaponAndAmmoAkimbo(const char* a1, C_TFPlayer* a2) = 0;
	virtual bool OwnsWeaponAndAmmo(void) = 0;

public:
	NETVAR(m_bDisableSpin, bool, "CWeaponSpawner", "m_bDisableSpin");
	NETVAR(m_bDisableShowOutline, bool, "CWeaponSpawner", "m_bDisableShowOutline");
	NETVAR(m_bRespawning, bool, "CWeaponSpawner", "m_bRespawning");
	NETVAR(m_bInitialDelay, bool, "CWeaponSpawner", "m_bInitialDelay");
	NETVAR(m_bSuperWeapon, bool, "CWeaponSpawner", "m_bSuperWeapon");
	NETVAR(fl_RespawnTime, float, "CWeaponSpawner", "fl_RespawnTime");
	NETVAR(m_flRespawnTick, float, "CWeaponSpawner", "m_flRespawnTick");
	NETVAR(fl_RespawnDelay, float, "CWeaponSpawner", "fl_RespawnDelay");
	//NETVAR(m_szWeaponName, const char*, "CWeaponSpawner", "m_szWeaponName");

public:
	//mf nigga shit
	inline void GetWeaponName(char* szName)
	{
		static const int s_nOff = H::NetVar.Get("CWeaponSpawner", "m_szWeaponName");

		int n;
		for (n = 0; n < 64; n++)
			szName[n] = *reinterpret_cast<char*>(reinterpret_cast<DWORD>(this) + (s_nOff + n));
	}
};

class C_CondPowerup : public C_BaseAnimating
{
public:
	virtual ~C_CondPowerup() = 0;

public:
	NETVAR(m_bDisableShowOutline, bool, "CCondPowerup", "m_bDisableShowOutline");
	NETVAR(m_bDisableIdleSound, bool, "CCondPowerup", "m_bDisableIdleSound");
	NETVAR(m_bRespawning, bool, "CCondPowerup", "m_bRespawning");
	NETVAR(m_bInitialDelay, bool, "CCondPowerup", "m_bInitialDelay");
	NETVAR(fl_RespawnTime, float, "CCondPowerup", "fl_RespawnTime");
	NETVAR(m_flRespawnTick, float, "CCondPowerup", "m_flRespawnTick");
	NETVAR(fl_RespawnDelay, float, "CCondPowerup", "fl_RespawnDelay");
	NETVAR(m_iCondition, int, "CCondPowerup", "m_iCondition");
};