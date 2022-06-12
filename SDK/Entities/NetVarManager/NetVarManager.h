#pragma once

#include "../../Interfaces/IInput.h"

class CHelpers_NetVarManager
{
public:
	int Get(const char* const szClass, const char* const szNetVar);

private:
	int GetOffset(RecvTable* pTable, const char* const szNetVar);
};

namespace H { inline CHelpers_NetVarManager NetVar; }

#define NETVAR(_name, type, table, name) inline type &_name() \
{ \
	static const int nOffset = H::NetVar.Get(table, name); \
	return *reinterpret_cast<type *>(reinterpret_cast<DWORD>(this) + nOffset); \
}