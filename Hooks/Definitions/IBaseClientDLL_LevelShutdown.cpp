#include "../../Hooks/Hooks.h"

DEFINE_HOOK(IBaseClientDLL_LevelShutdown, void, __fastcall, void* ecx, void* edx)
{
	Func.Original<FN>()(ecx, edx);
}