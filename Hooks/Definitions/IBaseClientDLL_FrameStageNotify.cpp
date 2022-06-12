#include "../../Hooks/Hooks.h"

DEFINE_HOOK(IBaseClientDLL_FrameStageNotify, void, __fastcall, void* ecx, void* edx, ClientFrameStage_t curStage)
{
	Func.Original<FN>()(ecx, edx, curStage);
}