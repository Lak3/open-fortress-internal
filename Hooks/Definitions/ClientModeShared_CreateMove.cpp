#include "../Hooks.h"

#include "../../Features/EnginePrediction/EnginePrediction.h"

DEFINE_HOOK(ClientModeShared_CreateMove, bool, __fastcall, void* ecx, void* edx, float input_sample_frametime, CUserCmd* cmd)
{
	if (!cmd || !cmd->command_number)
		return Func.Original<FN>()(ecx, edx, input_sample_frametime, cmd);

	F::EnginePrediction.Start(cmd);
	{
		//AIMPOT();
		//TRIGGERPOT();
	}
	F::EnginePrediction.Finish();

	return false;
}