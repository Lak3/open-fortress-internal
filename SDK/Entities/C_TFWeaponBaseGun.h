#pragma once

#include "C_TFWeaponBase.h"

//Types here might be wrong.
class C_TFWeaponBaseGun : public C_TFWeaponBase
{
public:
	virtual			~C_TFWeaponBaseGun() = 0;

	virtual void	DoViewModelAnimation(void) = 0;
	virtual void	DoFireEffects(void) = 0;
	virtual void	FireProjectile(C_TFPlayer* a1) = 0;
	virtual float	GetWeaponSpread(void) = 0;
	virtual float	GetProjectileDamage(void) = 0;
	virtual void	ZoomIn(void) = 0;
	virtual void	ZoomOut(void) = 0;

public:
	NETVAR(m_flAccurateAtTick, float, "CTFWeaponBaseGun", "m_flAccurateAtTick");
};