#include "Offsets.h"

#define GETPATT(x, mod, patt) x = U::Pattern.Find(mod, patt); XASSERT(x == 0x0)

void CUtil_Offsets::Initialize()
{
	GETPATT(m_dwClientModeCreateMove, "client.dll", "55 8B EC E8 ? ? ? ? 8B C8 85 C9 75 06 B0 01 5D C2 08 00");
	GETPATT(m_dwCTFDiscordRPC_Reset, "client.dll", "56 57 8B F1 6A 48 6A 00 8D 7E 10 57 E8 ? ? ? ? C7 46 ? ? ? ? ? 83 C4 0C C7 07 ? ? ? ? A1 ? ? ? ? 8B 48 04 85 C9 74 71");
	GETPATT(m_dwCTFDiscordRPC_LevelInit, "client.dll", "55 8B EC 56 57 8B F9 E8 ? ? ? ? 8B 55 08 8D B7 ? ? ? ?");
	GETPATT(m_dwIInput_GetUserCmd, "client.dll", "55 8B EC 53 56 8B D9 8B 4D 08 57 E8 ? ? ? ? 8B 75 0C 8B F8 B8 ? ? ? ?");
	GETPATT(m_dwIInput, "client.dll", "8B 0D ? ? ? ? 8B 01 FF 60 44");
	GETPATT(m_dwC_BasePlayer_CalcPlayerView, "client.dll", "55 8B EC 83 EC 18 53 56 8B F1 8B 0D ? ? ? ? 57 8B 01");
	GETPATT(m_dwC_BaseEntity_SetPredictionRandomSeed, "client.dll", "55 8B EC 8B 45 08 85 C0 75 0C");
	GETPATT(m_dwC_BaseEntity_Instance, "client.dll", "55 8B EC FF 75 08 8B 0D ? ? ? ? E8 ? ? ? ? 5D C3");
	GETPATT(m_dwC_BasePlayer_UpdateButtonState, "client.dll", "55 8B EC 8B 81 ? ? ? ? 8B D0 56 8B 75 08 33 D6");
	GETPATT(m_dwC_BasePlayer_UsingStandardWeaponsInVehicle, "client.dll", "56 57 8B F9 8B B7 ? ? ? ? 83 FE FF 74 48");
	GETPATT(m_dwC_BaseCombatWeapon_GetWpnData, "client.dll", "0F B7 81 ? ? ? ? 50 E8 ? ? ? ? 83 C4 04 C3");
	GETPATT(m_dwC_TFPlayerShared_InCondInvis, "client.dll", "56 57 8B F9 8D 77 20 8B 46 E0 8D 4E E0 56 FF 50 04 F6 06 10 75 17");
	GETPATT(m_dwC_TFPlayerShared_InCondUber, "client.dll", "56 57 8B F9 8D 77 20 8B 46 E0 8D 4E E0 56 FF 50 04 F6 06 20 75 17");
	GETPATT(m_dwC_TFPlayerShared_InCond, "client.dll", "55 8B EC 56 8B 75 08 57 81 FE ? ? ? ? 7D 54");
	GETPATT(m_dwSharedRandomInt, "client.dll", "55 8B EC 83 EC 08 8B 45 14 89 45 F8 A1 ? ? ? ? 89 45 FC 8D 45 14 56");
	GETPATT(m_dwCTFGameMovement_ProcessMovement, "client.dll", "55 8B EC 53 8B 5D 08 56 8B F1 85 DB 0F 84 ? ? ? ? 57 8B 7D 0C 85 FF 0F 84 ? ? ? ?");
	GETPATT(m_dwC_TFPlayer_TeamFortress_SetSpeed, "client.dll", "55 8B EC 83 EC 08 53 56 8B F1 8B 06 8B 9E ? ? ? ?");

	GETPATT(m_dwGlobalVars, "engine.dll", "A1 ? ? ? ? 8B 11 68");
	GETPATT(m_dwCNetChan_Shutdown, "engine.dll", "55 8B EC 83 EC 10 56 8B F1 83 BE ? ? ? ? ? 0F 8C ? ? ? ?");
	GETPATT(m_dwCNetChan_SendNetMsg, "engine.dll", "55 8B EC 57 8B F9 8D 8F ? ? ? ? E8 ? ? ? ? 85 C0 75 07");
	GETPATT(m_dwClientState, "engine.dll", "B9 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? 83 78 1C 00");

	GETPATT(m_dwStartDrawing, "vguimatsurface.dll", "55 8B EC 64 A1 ? ? ? ? 6A FF 68 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 14");
	GETPATT(m_dwFinishDrawing, "vguimatsurface.dll", "55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 51 56 6A 00");
}