#include "Hooks.h"

void CGlobal_Hooks::Initialize()
{
	XASSERT(MH_Initialize() != MH_STATUS::MH_OK);

	Hooks::CNetChan_Shutdown::Initialize();
	Hooks::CPrediction_RunCommand::Initialize();
	Hooks::IBaseClientDLL_FrameStageNotify::Initialize();
	Hooks::IBaseClientDLL_LevelShutdown::Initialize();
	Hooks::ClientModeShared_CreateMove::Initialize();
	Hooks::CTFDiscordRPC_LevelInit::Initialize();
	Hooks::CTFDiscordRPC_Reset::Initialize();
	Hooks::IEngineVGui_Paint::Initialize();

	XASSERT(MH_EnableHook(MH_ALL_HOOKS) != MH_STATUS::MH_OK);

	I::Cvar->ConsoleColorPrintf({ 15, 150, 150, 255 }, "[Only Fortress] CGlobal_Hooks::Initialize() finished!\n");
}