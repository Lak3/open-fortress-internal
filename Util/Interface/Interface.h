#pragma once

#include "../VFunc/VFunc.h"

typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);

class CUtil_Interface
{
public:
	template<typename T>
	inline T Get(const char* const szModule, const char* const szObject)
	{
		const HMODULE hMod = GetModuleHandleA(szModule);

		if (!hMod)
			return NULL;

		void* pRet = GetInterfaceInternal(hMod, szObject);

		if (pRet)
		{
			return static_cast<T>(pRet);
		}
		else
		{
			MessageBoxA(HWND_DESKTOP, szObject, "Failed to find interface:", MB_ICONERROR);
			return NULL;
		}
	}

private:
	void* GetInterfaceInternal(const HMODULE hModule, const char* const szObject);
};

namespace U { inline CUtil_Interface Interface; }