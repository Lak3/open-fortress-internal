#include "Interface.h"

void* CUtil_Interface::GetInterfaceInternal(const HMODULE hModule, const char* const szObject)
{
	const FARPROC pfCreateAddr = GetProcAddress(hModule, "CreateInterface");

	if (!pfCreateAddr)
		return nullptr;

	const CreateInterfaceFn pfCreateInterface = reinterpret_cast<CreateInterfaceFn>(pfCreateAddr);

	if (!pfCreateInterface)
		return nullptr;

	return pfCreateInterface(szObject, nullptr);
}