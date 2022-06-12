#include "../Hooks.h"

DEFINE_HOOK(CTFDiscordRPC_Reset, int, __fastcall, void* ecx, void* edx)
{
	I::Cvar->ConsoleColorPrintf({ 15, 150, 150, 255 }, "[Only Fortress] CTFDiscordRPC::Reset() got called and was prevented from running!\n");

	return 0;
}