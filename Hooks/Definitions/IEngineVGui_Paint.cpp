#include "../Hooks.h"

#include "../../Features/ESP/ESP.h"

DEFINE_HOOK(IEngineVGui_Paint, void, __fastcall, void* ecx, void* edx, int mode)
{
	Func.Original<FN>()(ecx, edx, mode);

	if (mode & PAINT_UIPANELS)
	{
		I::MatSystemSurface->StartDrawing();
		{
			H::Draw.UpdateMatrix();

			F::ESP.Render();

			H::Draw.String(EFonts::DEBUG, 5, 5, { 255, 255, 255, 255 }, TXT_DEFAULT, L"Only Fortress by Lak3 & Spook953 - unknowncheats.me");
		}
		I::MatSystemSurface->FinishDrawing();
	}
}