#pragma once

#include "Helpers/Helpers.h"

namespace I { inline void* TFGameMovement = nullptr; }

namespace Util
{
	inline Color GetHealthColor(const int nHealth, const int nMaxHealth)
	{
		if (nHealth > nMaxHealth)
			return { 15, 150, 150, 255 };

		const int nHP = U::Math.Max(0, U::Math.Min(nHealth, nMaxHealth));

		const unsigned int nR = static_cast<unsigned int>(U::Math.Min((510 * (nMaxHealth - nHP)) / nMaxHealth, 200));
		const unsigned int nG = static_cast<unsigned int>(U::Math.Min((510 * nHP) / nMaxHealth, 200));

		return { static_cast<byte>(nR), static_cast<byte>(nG), 0, 255 };
	}
}