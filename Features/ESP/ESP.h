#pragma once

#include "../../SDK/SDK.h"

class CFeatures_ESP
{
public:
	void Render();
	void LevelInitPostEntity();

private:
	bool IsAmmo(const int nModelIndex);
	bool IsHealth(const int nModelIndex);
	bool GetDynamicBounds(C_BaseEntity* pEntity, int& x, int& y, int& w, int& h);

private:
	std::vector<int> m_vecHealth = { };
	std::vector<int> m_vecAmmo = { };
	std::map<int, const wchar_t*> m_mapPowerups = { };
};

namespace F { inline CFeatures_ESP ESP; }