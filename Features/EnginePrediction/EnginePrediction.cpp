#include "EnginePrediction.h"

void CFeatures_EnginePrediction::Start(CUserCmd* cmd)
{
	if (!I::MoveHelper)
		return;

	C_TFPlayer* pLocal = I::ClientEntityList->GetClientEntity(I::EngineClient->GetLocalPlayer())->As<C_TFPlayer*>();

	if (!pLocal)
		return;

	cmd->random_seed = (MD5_PseudoRandom(cmd->command_number) & INT_MAX);

	pLocal->SetCurrentCommand(cmd);
	C_BaseEntity::SetPredictionRandomSeed(cmd);
	C_BaseEntity::SetPredictionPlayer(pLocal);

	m_fOldCurrentTime = I::GlobalVarsBase->curtime;
	m_fOldFrameTime   = I::GlobalVarsBase->frametime;
	m_nOldTickCount   = I::GlobalVarsBase->tickcount;

	const int nOldTickBase           = pLocal->m_nTickBase();
	const bool bOldIsFirstPrediction = I::Prediction->m_bFirstTimePredicted;
	const bool bOldInPrediction      = I::Prediction->m_bInPrediction;

	const int nServerTicks = GetTickbase(pLocal, cmd);

	I::GlobalVarsBase->curtime   = TICKS_TO_TIME(nServerTicks);
	I::GlobalVarsBase->frametime = (I::Prediction->m_bEnginePaused ? 0.0f : TICK_INTERVAL);
	I::GlobalVarsBase->tickcount = nServerTicks;

	I::Prediction->m_bFirstTimePredicted = false;
	I::Prediction->m_bInPrediction       = true;

	I::GameMovement->StartTrackPredictionErrors(pLocal);

	if (cmd->weaponselect != 0)
	{
		C_BaseCombatWeapon* pWeapon = dynamic_cast<C_BaseCombatWeapon*>(C_BaseEntity::Instance(cmd->weaponselect));

		if (pWeapon)
			pLocal->SelectItem(pWeapon->GetName(), cmd->weaponsubtype);
	}

	if (cmd->impulse)
	{
		if (!pLocal->GetClientVehicle() || pLocal->UsingStandardWeaponsInVehicle())
			pLocal->m_nImpulse() = cmd->impulse;
	}

	pLocal->UpdateButtonState(cmd->buttons);

	I::Prediction->SetLocalViewAngles(cmd->viewangles);

	I::Prediction->SetupMove(pLocal, cmd, I::MoveHelper, &m_MoveData);
	I::GameMovement->ProcessMovement(pLocal, &m_MoveData);
	I::Prediction->FinishMove(pLocal, cmd, &m_MoveData);

	pLocal->m_nTickBase() = nOldTickBase;

	I::Prediction->m_bInPrediction       = bOldInPrediction;
	I::Prediction->m_bFirstTimePredicted = bOldIsFirstPrediction;
}

void CFeatures_EnginePrediction::Finish()
{
	if (!I::MoveHelper)
		return;

	C_TFPlayer* pLocal = I::ClientEntityList->GetClientEntity(I::EngineClient->GetLocalPlayer())->As<C_TFPlayer*>();

	if (!pLocal)
		return;

	I::GameMovement->FinishTrackPredictionErrors(pLocal);

	I::GlobalVarsBase->curtime   = m_fOldCurrentTime;
	I::GlobalVarsBase->frametime = m_fOldFrameTime;
	I::GlobalVarsBase->tickcount = m_nOldTickCount;

	pLocal->SetCurrentCommand(nullptr);
	C_BaseEntity::SetPredictionRandomSeed(nullptr);
	C_BaseEntity::SetPredictionPlayer(nullptr);
}

int CFeatures_EnginePrediction::GetTickbase(C_TFPlayer* pLocal, CUserCmd* cmd)
{
	static int       s_nTick    = 0;
	static CUserCmd* s_pLastCmd = nullptr;

	if (cmd)
	{
		if (!s_pLastCmd || s_pLastCmd->hasbeenpredicted)
			s_nTick = pLocal->m_nTickBase();
		else
			s_nTick++;

		s_pLastCmd = cmd;
	}

	return s_nTick;
}