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
};

namespace U { inline CUtil_Offsets Offsets; }