#include "VFunc.h"

void**& CUtil_VFunc::Get_VTable(void* inst, const unsigned int offset)
{
	return *reinterpret_cast<void***>(reinterpret_cast<unsigned int>(inst) + offset);
}

const void** CUtil_VFunc::Get_VTable(const void* inst, const unsigned int offset)
{
	return *reinterpret_cast<const void***>(reinterpret_cast<unsigned int>(inst) + offset);
}