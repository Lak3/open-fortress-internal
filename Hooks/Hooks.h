#pragma once

#include "../SDK/SDK.h"

CREATE_HOOK(ClientModeShared_CreateMove, U::Offsets.m_dwClientModeCreateMove, bool, __fastcall, void* ecx, void* edx, float input_sample_frametime, CUserCmd* cmd);
CREATE_HOOK(IEngineVGui_Paint, U::VFunc.Get<void*>(I::EngineVGui, 13u), void, __fastcall, void* ecx, void* edx, int mode);
CREATE_HOOK(CTFDiscordRPC_Reset, U::Offsets.m_dwCTFDiscordRPC_Reset, int, __fastcall, void* ecx, void* edx);
CREATE_HOOK(CTFDiscordRPC_LevelInit, U::Offsets.m_dwCTFDiscordRPC_LevelInit, void*, __fastcall, void* ecx, void* edx, const char* a1);
CREATE_HOOK(IBaseClientDLL_FrameStageNotify, U::VFunc.Get<void*>(I::BaseClientDLL, 35u), void, __fastcall, void* ecx, void* edx, ClientFrameStage_t curStage);
CREATE_HOOK(IBaseClientDLL_LevelShutdown, U::VFunc.Get<void*>(I::BaseClientDLL, 7u), void, __fastcall, void* ecx, void* edx);
CREATE_HOOK(IBaseClientDLL_LevelInitPostEntity, U::VFunc.Get<void*>(I::BaseClientDLL, 6u), void, __fastcall, void* ecx, void* edx);
CREATE_HOOK(CPrediction_RunCommand, U::VFunc.Get<void*>(I::Prediction, 17u), void, __fastcall, void* ecx, void* edx, C_BasePlayer* player, CUserCmd* ucmd, IMoveHelper* moveHelper);
CREATE_HOOK(CNetChan_Shutdown, U::Offsets.m_dwCNetChan_Shutdown, void, __fastcall, void* ecx, void* edx, const char* pReason);
CREATE_HOOK(CTFGameMovement_ProcessMovement, U::Offsets.m_dwCTFGameMovement_ProcessMovement, void, __fastcall, void* ecx, void* edx, C_BasePlayer* pPlayer, CMoveData* pMove);

class CGlobal_Hooks
{
public:
	void Initialize();
};

namespace G { inline CGlobal_Hooks Hooks; }