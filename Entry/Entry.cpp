#include "Entry.h"

void CGlobal_Entry::Load()
{
	U::Offsets.Initialize();

	//Interfaces
	{
		I::BaseClientDLL = U::Interface.Get<IBaseClientDLL*>("client.dll", "VClient017");
		I::ClientEntityList = U::Interface.Get<IClientEntityList*>("client.dll", "VClientEntityList003");
		I::GameMovement = U::Interface.Get<IGameMovement*>("client.dll", "GameMovement001");
		I::Prediction = U::Interface.Get<CPrediction*>("client.dll", "VClientPrediction001");

		I::EngineClient = U::Interface.Get<IVEngineClient013*>("engine.dll", "VEngineClient013");
		I::EngineVGui = U::Interface.Get<IEngineVGui*>("engine.dll", "VEngineVGui001");
		I::RenderView = U::Interface.Get<IVRenderView*>("engine.dll", "VEngineRenderView014");
		I::GameEventManager = U::Interface.Get<IGameEventManager2*>("engine.dll", "GAMEEVENTSMANAGER002");
		I::EngineTraceClient = U::Interface.Get<IEngineTrace*>("engine.dll", "EngineTraceClient003");
		I::ModelInfoClient = U::Interface.Get<IVModelInfoClient*>("engine.dll", "VModelInfoClient006");

		I::MatSystemSurface = U::Interface.Get<IMatSystemSurface*>("vguimatsurface.dll", "VGUI_Surface030");

		I::Cvar = U::Interface.Get<ICvar*>("vstdlib.dll", "VEngineCvar004");

		//Other shenanigans
		{
			I::Input = **reinterpret_cast<IInput***>(U::Offsets.m_dwIInput + 0x2);
			XASSERT(I::Input == nullptr);

			I::GlobalVarsBase = *reinterpret_cast<CGlobalVarsBase**>(U::Offsets.m_dwGlobalVars + 0x8);
			XASSERT(I::GlobalVarsBase == nullptr);
		}
	}

	H::Draw.Initialize();

	G::Hooks.Initialize();

	I::Cvar->ConsoleColorPrintf({ 15, 150, 150, 255 }, "[Only Fortress] CGlobal_Entry::Load() finished!\n");
}