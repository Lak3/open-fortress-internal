#pragma once

#include "IVModelInfoClient.h"

typedef CBaseHandle EntityHandle_t;

class C_BasePlayer;

class CMoveData
{
public:
	bool m_bFirstRunOfFunctions : 1;
	bool m_bGameCodeMovedPlayer : 1;
	EntityHandle_t	m_nPlayerHandle;
	int m_nImpulseCommand;
	Vector m_vecViewAngles;
	Vector m_vecAbsViewAngles;
	int m_nButtons;
	int m_nOldButtons;
	float m_flForwardMove;
	float m_flOldForwardMove;
	float m_flSideMove;
	float m_flUpMove;
	float m_flMaxSpeed;
	float m_flClientMaxSpeed;
	Vector m_vecVelocity;
	Vector m_vecAngles;
	Vector m_vecOldAngles;
	float m_outStepHeight;
	Vector m_outWishVel;
	Vector m_outJumpVel;
	Vector m_vecConstraintCenter;
	float m_flConstraintRadius;
	float m_flConstraintWidth;
	float m_flConstraintSpeedFactor;
	Vector m_vecAbsOrigin;
};

class IGameMovement
{
public:
	virtual ~IGameMovement(void) {}
	virtual void ProcessMovement(C_BasePlayer* pPlayer, CMoveData* pMove) = 0;
	virtual void StartTrackPredictionErrors(C_BasePlayer* pPlayer) = 0;
	virtual void FinishTrackPredictionErrors(C_BasePlayer* pPlayer) = 0;
	virtual void DiffPrint(char const* fmt, ...) = 0;
	virtual Vector GetPlayerMins(bool ducked) const = 0;
	virtual Vector GetPlayerMaxs(bool ducked) const = 0;
	virtual Vector GetPlayerViewOffset(bool ducked) const = 0;
};

namespace I { inline IGameMovement* GameMovement = nullptr; }