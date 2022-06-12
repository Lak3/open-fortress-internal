#include "../../Hooks/Hooks.h"

DEFINE_HOOK(CPrediction_RunCommand, void, __fastcall, void* ecx, void* edx, C_BasePlayer* player, CUserCmd* ucmd, IMoveHelper* moveHelper)
{
	Func.Original<FN>()(ecx, edx, player, ucmd, moveHelper);

	if (!I::MoveHelper)
		I::MoveHelper = moveHelper;
}