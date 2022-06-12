#pragma once

#include "C_BaseFlex.h"

#define BCC_DEFAULT_LOOK_TOWARDS_TOLERANCE 0.9f

class C_BaseCombatCharacter : public C_BaseFlex
{
public:
	enum LineOfSightCheckType {
		IGNORE_NOTHING,
		IGNORE_ACTORS
	};

public:
	virtual							~C_BaseCombatCharacter() = 0;

	virtual bool					IsLookingTowards(const C_BaseEntity* target, float cosTolerance = BCC_DEFAULT_LOOK_TOWARDS_TOLERANCE) const = 0;
	virtual bool					IsLookingTowards(const Vector& target, float cosTolerance = BCC_DEFAULT_LOOK_TOWARDS_TOLERANCE) const = 0;
	virtual bool					IsInFieldOfView(C_BaseEntity* entity) const = 0;
	virtual bool					IsInFieldOfView(const Vector& pos) const = 0;
	virtual bool					IsLineOfSightClear(C_BaseEntity* entity, LineOfSightCheckType checkType = IGNORE_NOTHING) const = 0;
	virtual bool					IsLineOfSightClear(const Vector& pos, LineOfSightCheckType checkType = IGNORE_NOTHING, C_BaseEntity* entityToIgnore = NULL) const = 0;
	virtual	bool					Weapon_Switch(C_BaseCombatWeapon* pWeapon, int viewmodelindex = 0) = 0;
	virtual bool					Weapon_CanSwitchTo(C_BaseCombatWeapon* pWeapon) = 0;
	virtual C_BaseCombatWeapon*     GetActiveWeapon(void) const = 0;

public:
	NETVAR(m_flNextAttack, float, "CBaseCombatCharacter", "m_flNextAttack");
	NETVAR(m_hActiveWeapon, int, "CBaseCombatCharacter", "m_hActiveWeapon");
	NETVAR(m_hMyWeapons, void*, "CBaseCombatCharacter", "m_hMyWeapons");
	NETVAR(m_iWeaponCount, int, "CBaseCombatCharacter", "m_iWeaponCount");
};