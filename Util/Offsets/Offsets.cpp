#include "Offsets.h"

#define GETPATT(x, mod, patt) x = U::Pattern.Find(mod, patt); XASSERT(x == 0x0)

void CUtil_Offsets::Initialize()
{
	GETPATT(m_dwClientModeCreateMove, "client.dll", "55 8B EC E8 ? ? ? ? 8B C8 85 C9 75 06 B0 01 5D C2 08 00");
	GETPATT(m_dwCTFDiscordRPC_Reset, "client.dll", "56 57 8B F1 6A 48 6A 00 8D 7E 10 57 E8 ? ? ? ? C7 46 ? ? ? ? ? 83 C4 0C C7 07 ? ? ? ? A1 ? ? ? ? 8B 48 04 85 C9 74 71");
	GETPATT(m_dwCTFDiscordRPC_LevelInit, "client.dll", "55 8B EC 56 57 8B F9 E8 ? ? ? ? 8B 55 08 8D B7 ? ? ? ?");
	GETPATT(m_dwIInput_GetUserCmd, "client.dll", "55 8B EC 53 56 8B D9 8B 4D 08 57 E8 ? ? ? ? 8B 75 0C 8B F8 B8 ? ? ? ?");
	GETPATT(m_dwIInput, "client.dll", "8B 0D ? ? ? ? 8B 01 FF 60 44");

	GETPATT(m_dwGlobalVars, "engine.dll", "A1 ? ? ? ? 8B 11 68");
	GETPATT(m_dwCNetChan_Shutdown, "engine.dll", "55 8B EC 83 EC 10 56 8B F1 83 BE ? ? ? ? ? 0F 8C ? ? ? ?");

	GETPATT(m_dwStartDrawing, "vguimatsurface.dll", "55 8B EC 64 A1 ? ? ? ? 6A FF 68 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 14");
	GETPATT(m_dwFinishDrawing, "vguimatsurface.dll", "55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 51 56 6A 00");
}