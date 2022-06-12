#include "../../Hooks/Hooks.h"

DEFINE_HOOK(CNetChan_Shutdown, void, __fastcall, void* ecx, void* edx, const char* pReason)
{
	I::Cvar->ConsoleColorPrintf({ 15, 150, 150, 255 }, "CNetChan::Shutdown() got called, replaced argument with custom string.\n");

	Func.Original<FN>()(ecx, edx, "Greetings from Spook953 and Lak3 =)");
}