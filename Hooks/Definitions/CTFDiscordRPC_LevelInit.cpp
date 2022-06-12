#include "../Hooks.h"

DEFINE_HOOK(CTFDiscordRPC_LevelInit, void*, __fastcall, void* ecx, void* edx, const char* a1)
{
	I::Cvar->ConsoleColorPrintf({ 15, 150, 150, 255 }, "[Only Fortress] CTFDiscordRPC::LevelInit() got called, replaced argument with custom string.\n");

	return Func.Original<FN>()(ecx, edx, "Spook953 and Lak3 was here");
}