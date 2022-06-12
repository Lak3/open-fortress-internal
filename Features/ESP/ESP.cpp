#include "ESP.h"

#include "../Vars.h"

void CFeatures_ESP::Render()
{
	static bool s_bIgnoreTeam = false;

	if (I::EngineVGui->IsGameUIVisible() || !I::EngineClient->IsInGame())
		return;

	int n, x, y, w, h;

	const int nMaxClients = (I::EngineClient->GetMaxClients() + 1);
	const int nLocalIndex = I::EngineClient->GetLocalPlayer();

	C_TFPlayer* pLocal = I::ClientEntityList->GetClientEntity(nLocalIndex)->As<C_TFPlayer*>();

	if (!pLocal)
		return;

	player_info_t pi;
	for (n = 1; n < nMaxClients; n++)
	{
		if (n == nLocalIndex)
			continue;

		IClientEntity* pEntity = I::ClientEntityList->GetClientEntity(n);

		if (!pEntity || pEntity->IsDormant())
			continue;

		C_TFPlayer* pPlayer = pEntity->As<C_TFPlayer*>();

		if (!pPlayer || pPlayer->deadflag())
			continue;

		if (s_bIgnoreTeam && pPlayer->InLocalTeam())
			continue;

		const int nHealth = pPlayer->GetHealth();
		const int nMaxHealth = pPlayer->GetMaxHealth();

		if (!nHealth || !nMaxHealth || !GetDynamicBounds(pPlayer, x, y, w, h))
			continue;

		float r, g, b;
		pPlayer->GetGlowEffectColor(&r, &g, &b);

		const Color clrRender = { static_cast<byte>(r * 255.0f), static_cast<byte>(g * 255.0f), static_cast<byte>(b * 255.0f), 255 };
		const Color clrHealth = Util::GetHealthColor(nHealth, nMaxHealth);

		//if (box)
		{
			H::Draw.OutlinedRect(x, y, w, h, clrRender);

			//Outline
			H::Draw.OutlinedRect(x - 1, y - 1, w + 2, h + 2, { 1, 1, 1, 255 });

			//Inline
			H::Draw.OutlinedRect(x + 1, y + 1, w - 2, h - 2, { 1, 1, 1, 255 });
		}

		if (I::EngineClient->GetPlayerInfo(n, &pi))
		{
			H::Draw.String(EFonts::ESP_NAME,
				x + (w / 2),
				y - (H::Draw.GetFontHeight(EFonts::ESP_NAME) + 2),
				{ 255, 255, 255, 255 },
				TXT_CENTERX,
				Util::ConvertUtf8ToWide(pi.name).c_str());
		}

		const int nDrawX = x + (w + 3);
		int nDrawY = y;

		//if (health_text)
		{
			H::Draw.String(EFonts::ESP, nDrawX, nDrawY, clrHealth, TXT_DEFAULT, L"%i/%i", nHealth, nMaxHealth);
			nDrawY += H::Draw.GetFontHeight(EFonts::ESP);
		}

		//if (conditions)
		{
			if (pPlayer->m_nPlayerCondEx4() & 0x1)
			{
				H::Draw.String(EFonts::ESP, nDrawX, nDrawY, { 230, 255, 110, 255 }, TXT_DEFAULT, L"PROTECTED");
				nDrawY += H::Draw.GetFontHeight(EFonts::ESP);
			}
		}

		//if (active_weapon)
		{
			C_BaseCombatWeapon* pWeapon = pPlayer->GetActiveWeapon();

			if (pWeapon)
			{
				std::string szWeapon = (pWeapon->GetName() + 10);

				//Some of the names are all caps, some all lowercase, some mixed so lets just convert to lowercase.
				std::transform(szWeapon.begin(), szWeapon.end(), szWeapon.begin(),
					[](unsigned char c) { return std::tolower(c); });

				H::Draw.String(EFonts::ESP_WEAPON,
					x + (w / 2),
					y + (h + 2),
					{ 191, 191, 191, 255 },
					TXT_CENTERX,
					szWeapon.c_str());
			}
		}

		//if (health_bar)
		{
			x -= 1;

			const float flMaxHealth = static_cast<float>(nMaxHealth);
			const float flHealth = U::Math.Clamp<float>(static_cast<float>(nHealth), 1.0f, flMaxHealth);

			static const int nWidth = 2;
			const int nHeight = (h + (flHealth < flMaxHealth ? 2 : 1));
			const int nHeight2 = (h + 1);

			const float ratio = (flHealth / flMaxHealth);
			H::Draw.Rect(static_cast<int>(((x - nWidth) - 2)), static_cast<int>((y + nHeight - (nHeight * ratio))), nWidth, static_cast<int>((nHeight * ratio)), clrHealth);
			H::Draw.OutlinedRect(static_cast<int>(((x - nWidth) - 2) - 1), static_cast<int>((y + nHeight - (nHeight * ratio)) - 1), nWidth + 2, static_cast<int>((nHeight * ratio) + 1), { 1, 1, 1, 255 });

			x += 1;
		}
	}
}

bool CFeatures_ESP::GetDynamicBounds(C_BaseEntity* pEntity, int& x, int& y, int& w, int& h)
{
	Vector vPoints[8];
	U::Math.BuildTransformedBox(vPoints, pEntity->m_vecMins(), pEntity->m_vecMaxs(), pEntity->RenderableToWorldTransform());

	Vector2D flb, brt, blb, frt, frb, brb, blt, flt;

	if (H::Draw.WorldPosToScreenPos(vPoints[3], flb) && H::Draw.WorldPosToScreenPos(vPoints[5], brt)
		&& H::Draw.WorldPosToScreenPos(vPoints[0], blb) && H::Draw.WorldPosToScreenPos(vPoints[4], frt)
		&& H::Draw.WorldPosToScreenPos(vPoints[2], frb) && H::Draw.WorldPosToScreenPos(vPoints[1], brb)
		&& H::Draw.WorldPosToScreenPos(vPoints[6], blt) && H::Draw.WorldPosToScreenPos(vPoints[7], flt)
		&& H::Draw.WorldPosToScreenPos(vPoints[6], blt) && H::Draw.WorldPosToScreenPos(vPoints[7], flt))
	{
		const Vector2D arr[8] = { flb, brt, blb, frt, frb, brb, blt, flt };

		float left = flb.x;
		float top = flb.y;
		float righ = flb.x;
		float bottom = flb.y;

		for (int n = 1; n < 8; n++)
		{
			if (left > arr[n].x)
				left = arr[n].x;

			if (top < arr[n].y)
				top = arr[n].y;

			if (righ < arr[n].x)
				righ = arr[n].x;

			if (bottom > arr[n].y)
				bottom = arr[n].y;
		}

		x = static_cast<int>(left);
		y = static_cast<int>(bottom);
		w = static_cast<int>((righ - left));
		h = static_cast<int>((top - bottom));

		return !(x > H::Draw.m_nScreenW || (x + w) < 0 || y > H::Draw.m_nScreenH || (y + h) < 0);
	}

	return false;
}