#pragma once

#include "C_BasePlayer.h"

class C_TFPlayer : public C_BasePlayer
{
public:
	virtual				~C_TFPlayer() = 0;

	virtual void		CalcViewBob(Vector& unk1) = 0;
	virtual void		CalcViewIdle(Vector& unk1) = 0;

public:
	NETVAR(m_bSaveMeParity, bool, "CTFPlayer", "m_bSaveMeParity");
	NETVAR(m_bChatting, bool, "CTFPlayer", "m_bChatting");
	NETVAR(m_bRetroMode, bool, "CTFPlayer", "m_bRetroMode");
	NETVAR(m_bIsRobot, bool, "CTFPlayer", "m_bIsRobot");
	NETVAR(m_bHauling, bool, "CTFPlayer", "m_bHauling");
	NETVAR(m_hRagdoll, int, "CTFPlayer", "m_hRagdoll");
	NETVAR(m_PlayerClass, void*, "CTFPlayer", "m_PlayerClass");
	NETVAR(m_iClass, int, "CTFPlayer", "m_iClass");
	NETVAR(m_iModifiers, int, "CTFPlayer", "m_iModifiers");
	NETVAR(m_iOldClass, int, "CTFPlayer", "m_iOldClass");
	NETVAR(m_iOldModifiers, int, "CTFPlayer", "m_iOldModifiers");
	NETVAR(pLocalData, void*, "CTFPlayer", "pLocalData");
	NETVAR(m_szModelName, const char*, "CTFPlayer", "m_szModelName");
	NETVAR(m_szArmModelName, const char*, "CTFPlayer", "m_szArmModelName");
	NETVAR(m_szLocalizableName, const char*, "CTFPlayer", "m_szLocalizableName");
	NETVAR(m_szJumpSound, const char*, "CTFPlayer", "m_szJumpSound");
	NETVAR(m_flMaxSpeed, float, "CTFPlayer", "m_flMaxSpeed");
	NETVAR(m_nMaxHealth, int, "CTFPlayer", "m_nMaxHealth");
	NETVAR(m_nMaxArmor, int, "CTFPlayer", "m_nMaxArmor");
	NETVAR(m_nArmorType, int, "CTFPlayer", "m_nArmorType");
	NETVAR(m_aWeapons, void*, "CTFPlayer", "m_aWeapons");
	NETVAR(m_aGrenades, void*, "CTFPlayer", "m_aGrenades");
	NETVAR(m_aAmmoMax, void*, "CTFPlayer", "m_aAmmoMax");
	NETVAR(m_aBuildable, void*, "CTFPlayer", "m_aBuildable");
	NETVAR(m_nCapNumber, int, "CTFPlayer", "m_nCapNumber");
	NETVAR(m_nMaxAirDashCount, int, "CTFPlayer", "m_nMaxAirDashCount");
	NETVAR(m_bDontDoAirwalk, bool, "CTFPlayer", "m_bDontDoAirwalk");
	NETVAR(m_bDontDoNewJump, bool, "CTFPlayer", "m_bDontDoNewJump");
	NETVAR(m_bSpecialClass, bool, "CTFPlayer", "m_bSpecialClass");
	NETVAR(m_szClassSelectImageRed, const char*, "CTFPlayer", "m_szClassSelectImageRed");
	NETVAR(m_szClassSelectImageBlue, const char*, "CTFPlayer", "m_szClassSelectImageBlue");
	NETVAR(m_szClassSelectImageMercenary, const char*, "CTFPlayer", "m_szClassSelectImageMercenary");
	NETVAR(m_szClassImageRed, const char*, "CTFPlayer", "m_szClassImageRed");
	NETVAR(m_szClassImageBlue, const char*, "CTFPlayer", "m_szClassImageBlue");
	NETVAR(m_szClassImageMercenary, const char*, "CTFPlayer", "m_szClassImageMercenary");
	NETVAR(m_szClassImageColorless, const char*, "CTFPlayer", "m_szClassImageColorless");
	NETVAR(m_szClassImageTennis, const char*, "CTFPlayer", "m_szClassImageTennis");
	NETVAR(m_szClassIcon, const char*, "CTFPlayer", "m_szClassIcon");
	NETVAR(m_nViewVector, int, "CTFPlayer", "m_nViewVector");
	NETVAR(m_bRefresh, bool, "CTFPlayer", "m_bRefresh");
	NETVAR(m_iSetCustomHealth, int, "CTFPlayer", "m_iSetCustomHealth");
	NETVAR(m_flSetCustomSpeed, float, "CTFPlayer", "m_flSetCustomSpeed");
	NETVAR(m_iszSetCustomModel, const char*, "CTFPlayer", "m_iszSetCustomModel");
	NETVAR(m_iszSetCustomArmModel, const char*, "CTFPlayer", "m_iszSetCustomArmModel");
	NETVAR(m_Shared, void*, "CTFPlayer", "m_Shared");
	NETVAR(m_nPlayerCond, int, "CTFPlayer", "m_nPlayerCond");
	NETVAR(m_nPlayerCondEx, int, "CTFPlayer", "m_nPlayerCondEx");
	NETVAR(m_nPlayerCondEx2, int, "CTFPlayer", "m_nPlayerCondEx2");
	NETVAR(m_nPlayerCondEx3, int, "CTFPlayer", "m_nPlayerCondEx3");
	NETVAR(m_nPlayerCondEx4, int, "CTFPlayer", "m_nPlayerCondEx4");
	NETVAR(m_bJumping, bool, "CTFPlayer", "m_bJumping");
	NETVAR(m_bIsTopThree, bool, "CTFPlayer", "m_bIsTopThree");
	NETVAR(bWatchReady, int, "CTFPlayer", "bWatchReady");
	NETVAR(m_bIsZombie, bool, "CTFPlayer", "m_bIsZombie");
	NETVAR(m_bIsLastSurvivor, bool, "CTFPlayer", "m_bIsLastSurvivor");
	NETVAR(m_nNumHealers, int, "CTFPlayer", "m_nNumHealers");
	NETVAR(m_iCritMult, int, "CTFPlayer", "m_iCritMult");
	NETVAR(m_bAirDash, bool, "CTFPlayer", "m_bAirDash");
	NETVAR(m_bBlockJump, bool, "CTFPlayer", "m_bBlockJump");
	NETVAR(m_iAirDashCount, int, "CTFPlayer", "m_iAirDashCount");
	NETVAR(m_bHovering, bool, "CTFPlayer", "m_bHovering");
	NETVAR(m_flGHookProp, float, "CTFPlayer", "m_flGHookProp");
	NETVAR(m_nPlayerState, int, "CTFPlayer", "m_nPlayerState");
	NETVAR(m_iDesiredPlayerClass, int, "CTFPlayer", "m_iDesiredPlayerClass");
	NETVAR(m_iRespawnEffect, int, "CTFPlayer", "m_iRespawnEffect");
	NETVAR(m_iArmor, int, "CTFPlayer", "m_iArmor");
	NETVAR(m_flInvisChangeCompleteTime, float, "CTFPlayer", "m_flInvisChangeCompleteTime");
	NETVAR(m_nDisguiseTeam, int, "CTFPlayer", "m_nDisguiseTeam");
	NETVAR(m_nDisguiseClass, int, "CTFPlayer", "m_nDisguiseClass");
	NETVAR(m_iDisguiseTargetIndex, int, "CTFPlayer", "m_iDisguiseTargetIndex");
	NETVAR(m_iDisguiseHealth, int, "CTFPlayer", "m_iDisguiseHealth");
	NETVAR(m_nDesiredDisguiseTeam, int, "CTFPlayer", "m_nDesiredDisguiseTeam");
	NETVAR(m_nDesiredDisguiseClass, int, "CTFPlayer", "m_nDesiredDisguiseClass");
	NETVAR(m_flStealthNoAttackExpire, float, "CTFPlayer", "m_flStealthNoAttackExpire");
	NETVAR(m_flStealthNextChangeTime, float, "CTFPlayer", "m_flStealthNextChangeTime");
	NETVAR(m_flNextLungeTime, float, "CTFPlayer", "m_flNextLungeTime");
	NETVAR(m_bNoAirControl, bool, "CTFPlayer", "m_bNoAirControl");
	NETVAR(m_flNextZoomTime, float, "CTFPlayer", "m_flNextZoomTime");
	NETVAR(m_flCloakMeter, float, "CTFPlayer", "m_flCloakMeter");
	NETVAR(m_Hook, int, "CTFPlayer", "m_Hook");
	NETVAR(m_pWeaponSpawner, int, "CTFPlayer", "m_pWeaponSpawner");
	NETVAR(m_bPlayerDominated, void*, "CTFPlayer", "m_bPlayerDominated");
	NETVAR(m_bPlayerDominatingMe, void*, "CTFPlayer", "m_bPlayerDominatingMe");
	NETVAR(m_flCondExpireTimeLeft, void*, "CTFPlayer", "m_flCondExpireTimeLeft");
	NETVAR(m_hItem, int, "CTFPlayer", "m_hItem");
	NETVAR(m_vecPlayerColor, Vector, "CTFPlayer", "m_vecPlayerColor");
	NETVAR(m_vecViewmodelOffset, Vector, "CTFPlayer", "m_vecViewmodelOffset");
	NETVAR(m_vecViewmodelAngle, Vector, "CTFPlayer", "m_vecViewmodelAngle");
	NETVAR(m_bCentered, bool, "CTFPlayer", "m_bCentered");
	NETVAR(m_bMinimized, bool, "CTFPlayer", "m_bMinimized");
	NETVAR(m_angEyeAngles, Vector, "CTFPlayer", "m_angEyeAngles[0]");
	NETVAR(m_iSpawnCounter, int, "CTFPlayer", "m_iSpawnCounter");
	NETVAR(m_bResupplied, bool, "CTFPlayer", "m_bResupplied");
	NETVAR(m_iAccount, int, "CTFPlayer", "m_iAccount");
	NETVAR(m_iMegaOverheal, int, "CTFPlayer", "m_iMegaOverheal");
};