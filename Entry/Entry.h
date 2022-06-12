#pragma once

#include "../Hooks/Hooks.h"

class CGlobal_Entry
{
public:
	void Load();
};

namespace G { inline CGlobal_Entry Entry; }