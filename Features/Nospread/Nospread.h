#pragma once

#include "../../SDK/SDK.h"

class CFeatures_Nospread
{
public:
	void Think(CUserCmd* pCommand);

private:
	bool CanWeaponNospread(const int nWeaponID);
	bool IsNeedleGun(const int nWeaponID);
};

namespace F { inline CFeatures_Nospread Nospread; }