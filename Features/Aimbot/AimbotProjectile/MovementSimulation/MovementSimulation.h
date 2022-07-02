#pragma once

#include "../../../../SDK/SDK.h"

class CAimbot_MovementSimulation
{
public:
	bool Initialize(C_TFPlayer* pPlayer);
	void Restore();
	void RunTick();

public:
	inline const Vector& GetOrigin() { return m_MoveData.m_vecAbsOrigin; }

private:
	void SetupMoveData(C_TFPlayer* pPlayer, CMoveData* pMoveData);

private:
	C_TFPlayer* m_pPlayer = nullptr;
	CMoveData   m_MoveData = { };
	CUserCmd    m_NullCmd = { };

	bool  m_bOldInPrediction = false;
	bool  m_bOldFirstTimePredicted = false;
	float m_flOldFrametime = 0.0f;
};

namespace A { inline CAimbot_MovementSimulation MovementSimulation; }

/* Player data backup stuff */
class CPlayerDataBackup
{
public:
	Vector m_vecOrigin = {};
	Vector m_vecVelocity = {};
	Vector m_vecBaseVelocity = {};
	Vector m_vecViewOffset = {};
	C_BaseEntity* m_hGroundEntity = nullptr;
	int m_fFlags = 0;
	float m_flDucktime = 0.0f;
	float m_flDuckJumpTime = 0.0f;
	bool m_bDucked = false;
	bool m_bDucking = false;
	bool m_bInDuckJump = false;
	float m_flModelScale = 0.0f;
	float m_flMaxspeed = 0.0f;
	bool m_bJumping = false;
	Vector m_vecPunchAngle = {};
	Vector m_vecPunchAngleVel = {};
	float m_flJumpTime = 0.0f;
	float m_flFallVelocity = 0.0f;
	int m_nPlayerCond = 0;
	int m_nPlayerCondEx = 0;
	int m_nPlayerCondEx2 = 0;
	int m_nPlayerCondEx3 = 0;
	int m_nPlayerCondEx4 = 0;

public:
	inline void Store(C_TFPlayer* pPlayer)
	{
		m_vecOrigin = pPlayer->m_vecOrigin();
		m_vecVelocity = pPlayer->m_vecVelocity();
		m_vecBaseVelocity = pPlayer->m_vecBaseVelocity();
		m_vecViewOffset = pPlayer->m_vecViewOffset();
		m_hGroundEntity = pPlayer->m_hGroundEntity();
		m_fFlags = pPlayer->m_fFlags();
		m_flDucktime = pPlayer->m_flDucktime();
		m_flDuckJumpTime = pPlayer->m_flDuckJumpTime();
		m_bDucked = pPlayer->m_bDucked();
		m_bDucking = pPlayer->m_bDucking();
		m_bInDuckJump = pPlayer->m_bInDuckJump();
		m_flModelScale = pPlayer->m_flModelScale();
		m_flMaxspeed = pPlayer->m_flMaxspeed();
		m_bJumping = pPlayer->m_bJumping();
		m_vecPunchAngle = pPlayer->m_vecPunchAngle();
		m_vecPunchAngleVel = pPlayer->m_vecPunchAngleVel();
		m_flFallVelocity = pPlayer->m_flFallVelocity();
		m_nPlayerCond = pPlayer->m_nPlayerCond();
		m_nPlayerCondEx = pPlayer->m_nPlayerCondEx();
		m_nPlayerCondEx2 = pPlayer->m_nPlayerCondEx2();
		m_nPlayerCondEx3 = pPlayer->m_nPlayerCondEx3();
		m_nPlayerCondEx4 = pPlayer->m_nPlayerCondEx4();
	}

	inline void Restore(C_TFPlayer* pPlayer)
	{
		pPlayer->m_vecOrigin() = m_vecOrigin;
		pPlayer->m_vecVelocity() = m_vecVelocity;
		pPlayer->m_vecBaseVelocity() = m_vecBaseVelocity;
		pPlayer->m_vecViewOffset() = m_vecViewOffset;
		pPlayer->m_hGroundEntity() = m_hGroundEntity;
		pPlayer->m_fFlags() = m_fFlags;
		pPlayer->m_flDucktime() = m_flDucktime;
		pPlayer->m_flDuckJumpTime() = m_flDuckJumpTime;
		pPlayer->m_bDucked() = m_bDucked;
		pPlayer->m_bDucking() = m_bDucking;
		pPlayer->m_bInDuckJump() = m_bInDuckJump;
		pPlayer->m_flModelScale() = m_flModelScale;
		pPlayer->m_flMaxspeed() = m_flMaxspeed;
		pPlayer->m_bJumping() = m_bJumping;
		pPlayer->m_vecPunchAngle() = m_vecPunchAngle;
		pPlayer->m_vecPunchAngleVel() = m_vecPunchAngleVel;
		pPlayer->m_flJumpTime() = m_flJumpTime;
		pPlayer->m_flFallVelocity() = m_flFallVelocity;
		pPlayer->m_nPlayerCond() = m_nPlayerCond;
		pPlayer->m_nPlayerCondEx() = m_nPlayerCondEx;
		pPlayer->m_nPlayerCondEx2() = m_nPlayerCondEx2;
		pPlayer->m_nPlayerCondEx3() = m_nPlayerCondEx3;
		pPlayer->m_nPlayerCondEx4() = m_nPlayerCondEx4;
	}
};

static CPlayerDataBackup g_PlayerDataBackup = { };