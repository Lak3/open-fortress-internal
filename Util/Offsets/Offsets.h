#pragma once

#include "../Pattern/Pattern.h"

class CUtil_Offsets
{
public:
	void Initialize();

public:
	DWORD m_dwClientModeCreateMove = 0x0;
	DWORD m_dwStartDrawing = 0x0;
	DWORD m_dwFinishDrawing = 0x0;
	DWORD m_dwCTFDiscordRPC_Reset = 0x0;
	DWORD m_dwCTFDiscordRPC_LevelInit = 0x0;
	DWORD m_dwIInput_GetUserCmd = 0x0;
	DWORD m_dwIInput = 0x0;
	DWORD m_dwGlobalVars = 0x0;
	DWORD m_dwCNetChan_Shutdown = 0x0;
	DWORD m_dwC_BasePlayer_CalcPlayerView = 0x0;
	DWORD m_dwCNetChan_SendNetMsg = 0x0;
	DWORD m_dwClientState = 0x0;
	DWORD m_dwC_BaseEntity_SetPredictionRandomSeed = 0x0;
	DWORD m_dwC_BaseEntity_Instance = 0x0;
	DWORD m_dwC_BasePlayer_UpdateButtonState = 0x0;
	DWORD m_dwC_BasePlayer_UsingStandardWeaponsInVehicle = 0x0;
	DWORD m_dwC_BaseCombatWeapon_GetWpnData = 0x0;
	DWORD m_dwC_TFPlayerShared_InCondInvis = 0x0;
	DWORD m_dwC_TFPlayerShared_InCondUber = 0x0;
	DWORD m_dwC_TFPlayerShared_InCond = 0x0;
	DWORD m_dwSharedRandomInt = 0x0;
	DWORD m_dwCTFGameMovement_ProcessMovement = 0x0;
	DWORD m_dwC_TFPlayer_TeamFortress_SetSpeed = 0x0;
};

namespace U { inline CUtil_Offsets Offsets; }