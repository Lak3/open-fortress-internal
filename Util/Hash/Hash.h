#pragma once

#include "../Offsets/Offsets.h"

class CUtil_Hash
{
public:
	int String(const char* szOrg);
};

namespace U { inline CUtil_Hash Hash; }

#define HASH_RT(str) U::Hash.String(str)