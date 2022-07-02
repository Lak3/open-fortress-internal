#include "../Hooks.h"

#include "../../Features/ESP/ESP.h"

DEFINE_HOOK(IBaseClientDLL_LevelInitPostEntity, void, __fastcall, void* ecx, void* edx)
{
	Func.Original<FN>()(ecx, edx);

	F::ESP.LevelInitPostEntity();
}