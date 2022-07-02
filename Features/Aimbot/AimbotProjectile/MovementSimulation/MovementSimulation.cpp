#include "MovementSimulation.h"

bool CAimbot_MovementSimulation::Initialize(C_TFPlayer* pPlayer)
{
	if (!I::TFGameMovement)
		return false;

	C_TFPlayer* pLocal = C_BaseEntity::Instance(I::EngineClient->GetLocalPlayer())->As<C_TFPlayer*>();

	if (!pLocal || !pPlayer || !pPlayer->IsAlive())
		return false;

	m_pPlayer = pPlayer;
	m_pPlayer->SetCurrentCommand(&m_NullCmd);

	g_PlayerDataBackup.Store(pPlayer);

	m_bOldInPrediction       = I::Prediction->m_bInPrediction;
	m_bOldFirstTimePredicted = I::Prediction->m_bFirstTimePredicted;
	m_flOldFrametime         = I::GlobalVarsBase->frametime;

	//the hacks that make it work
	{
		if (pPlayer->m_fFlags() & FL_DUCKING)
		{
			pPlayer->m_fFlags()         &= ~FL_DUCKING;
			pPlayer->m_bDucked()        = true;
			pPlayer->m_flDucktime()     = 0.0f;
			pPlayer->m_flDuckJumpTime() = 0.0f;
			pPlayer->m_bDucking()       = false;
			pPlayer->m_bInDuckJump()    = false;
		}

		if (pPlayer != pLocal)
			pPlayer->m_hGroundEntity() = nullptr;

		pPlayer->m_flModelScale() -= 0.03125f;

		if (pPlayer->m_fFlags() & FL_ONGROUND)
			pPlayer->m_vecOrigin().z += 0.03125f;

		if (::fabsf(pPlayer->m_vecVelocity().x) < 0.01f)
			pPlayer->m_vecVelocity().x = 0.015f;

		if (::fabsf(pPlayer->m_vecVelocity().y) < 0.01f)
			pPlayer->m_vecVelocity().y = 0.015f;
	}

	SetupMoveData(m_pPlayer, &m_MoveData);

	return true;
}

void CAimbot_MovementSimulation::Restore()
{
	if (!m_pPlayer)
		return;

	m_pPlayer->SetCurrentCommand(nullptr);

	g_PlayerDataBackup.Restore(m_pPlayer);

	I::Prediction->m_bInPrediction       = m_bOldInPrediction;
	I::Prediction->m_bFirstTimePredicted = m_bOldFirstTimePredicted;
	I::GlobalVarsBase->frametime         = m_flOldFrametime;

	m_pPlayer = nullptr;

	memset(&m_MoveData, 0, sizeof(CMoveData));
	memset(&g_PlayerDataBackup, 0, sizeof(CPlayerDataBackup));
}

void CAimbot_MovementSimulation::RunTick()
{
	if (!m_pPlayer || !I::TFGameMovement)
		return;

	I::Prediction->m_bInPrediction       = true;
	I::Prediction->m_bFirstTimePredicted = false;
	I::GlobalVarsBase->frametime         = I::Prediction->m_bEnginePaused ? 0.0f : TICK_INTERVAL;

	if (m_MoveData.m_vecVelocity.Lenght() < 15.0f && (m_pPlayer->m_fFlags() & FL_ONGROUND))
		return;

	//CTFGameMovement::ProcessMovement
	reinterpret_cast<void(__thiscall*)(void*, C_BasePlayer*, CMoveData*)>(U::Offsets.m_dwCTFGameMovement_ProcessMovement)(I::TFGameMovement, m_pPlayer, &m_MoveData);
}

void CAimbot_MovementSimulation::SetupMoveData(C_TFPlayer* pPlayer, CMoveData* pMoveData)
{
	if (!pPlayer || !pMoveData)
		return;

	//The var which this func sets seems to always be 0.
	//pPlayer->TeamFortress_SetSpeed();

	const Vector vecVelocity = pPlayer->m_vecVelocity();

	pMoveData->m_bFirstRunOfFunctions = false;
	pMoveData->m_bGameCodeMovedPlayer = false;
	pMoveData->m_nPlayerHandle        = pPlayer->GetRefEHandle();
	pMoveData->m_vecVelocity          = vecVelocity;
	pMoveData->m_vecAbsOrigin         = pPlayer->m_vecOrigin();
	pMoveData->m_flMaxSpeed           = pPlayer->m_flMaxspeed(); //C_TFPlayer::m_flMaxSpeed is always 0, this returns correct.

	if (g_PlayerDataBackup.m_fFlags & FL_DUCKING)
		pMoveData->m_flMaxSpeed *= 0.3333f;

	pMoveData->m_flClientMaxSpeed = pMoveData->m_flMaxSpeed;
	pMoveData->m_vecViewAngles    = { 0.0f, U::Math.VelocityToAngles(pMoveData->m_vecVelocity).y, 0.0f };

	//Assume full accel
	pMoveData->m_flForwardMove = 450.0f;
	pMoveData->m_flSideMove    = 0.0f;

	/*
	pMoveData->m_flForwardMove = (pMoveData->m_vecVelocity.y - vRight.y / vRight.x * pMoveData->m_vecVelocity.x) / (vForward.y - vRight.y / vRight.x * vForward.x);
	pMoveData->m_flSideMove = (pMoveData->m_vecVelocity.x - vForward.x * pMoveData->m_flForwardMove) / vRight.x;
	*/

	if (pPlayer->m_vecVelocity().Lenght2D() <= (pMoveData->m_flMaxSpeed * 0.1f))
		pMoveData->m_flForwardMove = pMoveData->m_flSideMove = 0.0f;

	pMoveData->m_vecAngles    = pMoveData->m_vecViewAngles;
	pMoveData->m_vecOldAngles = pMoveData->m_vecAngles;

	C_BaseEntity* pConstraintEntity = pPlayer->m_hConstraintEntity().Get();

	if (pConstraintEntity)
		pMoveData->m_vecConstraintCenter = pConstraintEntity->GetAbsOrigin();
	else
		pMoveData->m_vecConstraintCenter = pPlayer->m_vecConstraintCenter();

	pMoveData->m_flConstraintRadius      = pPlayer->m_flConstraintRadius();
	pMoveData->m_flConstraintWidth       = pPlayer->m_flConstraintWidth();
	pMoveData->m_flConstraintSpeedFactor = pPlayer->m_flConstraintSpeedFactor();
}