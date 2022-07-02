#include "ESP.h"

#include "../Vars.h"

void CFeatures_ESP::Render()
{
	static bool s_bIgnoreTeam = false;

	if (I::EngineVGui->IsGameUIVisible() || !I::EngineClient->IsInGame())
		return;

	int n, x, y, w, h;

	const int nMaxClients  = (I::EngineClient->GetMaxClients() + 1);
	const int nMaxEntities = I::ClientEntityList->GetMaxEntities();
	const int nLocalIndex  = I::EngineClient->GetLocalPlayer();

	C_TFPlayer* pLocal = I::ClientEntityList->GetClientEntity(nLocalIndex)->As<C_TFPlayer*>();

	if (!pLocal)
		return;

	Rect_t s;
	for (n = nMaxClients; n < nMaxEntities; n++)
	{
		C_BaseEntity* pEntity = C_BaseEntity::Instance(n);

		if (!pEntity || pEntity->IsDormant())
			continue;

		ClientClass* pCC = pEntity->GetClientClass();

		if (!pCC)
			continue;

		switch (pCC->m_ClassID)
		{
			case CTFAmmoPack:
			{
				if (!H::Draw.WorldPosToScreenPos(pEntity->WorldSpaceCenter(), s))
					break;

				H::Draw.String(EFonts::PICKUPS, s.x, s.y, COLOR_GREY, TXT_CENTERXY, L"ammo");

				break;
			}
			case CCondPowerup:
			{
				C_CondPowerup* pPowerup = pEntity->As<C_CondPowerup*>();

				if (!pPowerup || !H::Draw.WorldPosToScreenPos(pPowerup->WorldSpaceCenter(), s))
					break;

				const int nModelIndex = pPowerup->m_nModelIndex();

				if (m_mapPowerups.find(nModelIndex) == m_mapPowerups.end())
					break;

				H::Draw.String(EFonts::PICKUPS, s.x, s.y, COLOR_YELLOW, TXT_CENTERXY, m_mapPowerups[nModelIndex]);
				s.y += H::Draw.GetFontHeight(EFonts::PICKUPS);

				if (pPowerup->m_bRespawning())
				{
					const float flRespawn = (pPowerup->m_flRespawnTick() - I::GlobalVarsBase->curtime);

					H::Draw.String(EFonts::PICKUPS, s.x, s.y, COLOR_YELLOW, TXT_CENTERXY, L"%.1f", flRespawn);
					s.y += H::Draw.GetFontHeight(EFonts::PICKUPS);
				}

				break;
			}
			case CWeaponSpawner:
			{
				C_WeaponSpawner* pSpawn = pEntity->As<C_WeaponSpawner*>();

				if (!pSpawn || !H::Draw.WorldPosToScreenPos(pSpawn->WorldSpaceCenter(), s))
					break;

				const Color clrRender = pSpawn->m_bSuperWeapon() ? COLOR_YELLOW : COLOR_GREY;

				char szArray[64];
				pSpawn->GetWeaponName(szArray);

				std::string szWeapon = (szArray + 10);
				std::transform(szWeapon.begin(), szWeapon.end(), szWeapon.begin(),
					[](unsigned char c) { return ::tolower(c); });

				H::Draw.String(EFonts::PICKUPS, s.x, s.y, clrRender, TXT_CENTERXY, szWeapon.c_str());
				s.y += H::Draw.GetFontHeight(EFonts::PICKUPS);

				if (pSpawn->m_bRespawning())
				{
					const float flRespawn = (pSpawn->m_flRespawnTick() - I::GlobalVarsBase->curtime);

					H::Draw.String(EFonts::PICKUPS, s.x, s.y, clrRender, TXT_CENTERXY, L"%.1fs", flRespawn);
					s.y += H::Draw.GetFontHeight(EFonts::PICKUPS);
				}

				break;
			}
			case CBaseAnimating:
			{
				const int nModelIndex = pEntity->m_nModelIndex();

				if (IsAmmo(nModelIndex) && H::Draw.WorldPosToScreenPos(pEntity->WorldSpaceCenter(), s))
				{
					H::Draw.String(EFonts::PICKUPS, s.x, s.y, COLOR_GREY, TXT_CENTERXY, L"ammo");
					break;
				}

				if (IsHealth(nModelIndex) && H::Draw.WorldPosToScreenPos(pEntity->WorldSpaceCenter(), s))
				{
					H::Draw.String(EFonts::PICKUPS, s.x, s.y, COLOR_GREEN, TXT_CENTERXY, L"health");
					break;
				}

				break;
			}
			default:
				break;
		}
	}

	player_info_t pi;
	for (n = 1; n < nMaxClients; n++)
	{
		if (n == nLocalIndex)
			continue;

		C_BaseEntity* pEntity = C_BaseEntity::Instance(n);

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
			H::Draw.OutlinedRect(x - 1, y - 1, w + 2, h + 2, COLOR_BLACK);

			//Inline
			H::Draw.OutlinedRect(x + 1, y + 1, w - 2, h - 2, COLOR_BLACK);
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
			if (pPlayer->InCondUber())
			{
				H::Draw.String(EFonts::ESP, nDrawX, nDrawY, COLOR_YELLOW, TXT_DEFAULT, L"INVULNERABLE");
				nDrawY += H::Draw.GetFontHeight(EFonts::ESP);
			}

			if (pPlayer->InCondCrit())
			{
				H::Draw.String(EFonts::ESP, nDrawX, nDrawY, COLOR_YELLOW, TXT_DEFAULT, L"CRITS");
				nDrawY += H::Draw.GetFontHeight(EFonts::ESP);
			}

			if (pPlayer->InCondBerserk())
			{
				H::Draw.String(EFonts::ESP, nDrawX, nDrawY, COLOR_YELLOW, TXT_DEFAULT, L"BERSERK");
				nDrawY += H::Draw.GetFontHeight(EFonts::ESP);
			}

			if (pPlayer->InCondHaste())
			{
				H::Draw.String(EFonts::ESP, nDrawX, nDrawY, COLOR_YELLOW, TXT_DEFAULT, L"HASTE");
				nDrawY += H::Draw.GetFontHeight(EFonts::ESP);
			}

			if (pPlayer->InCondShield())
			{
				H::Draw.String(EFonts::ESP, nDrawX, nDrawY, COLOR_YELLOW, TXT_DEFAULT, L"SHIELD");
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
					COLOR_GREY,
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
			H::Draw.OutlinedRect(static_cast<int>(((x - nWidth) - 2) - 1), static_cast<int>((y + nHeight - (nHeight * ratio)) - 1), nWidth + 2, static_cast<int>((nHeight * ratio) + 1), COLOR_BLACK);

			x += 1;
		}
	}
}

void CFeatures_ESP::LevelInitPostEntity()
{
	m_vecAmmo.clear();
	{
		m_vecAmmo.push_back(I::ModelInfoClient->GetModelIndex("models/items/ammopack_large.mdl"));
		m_vecAmmo.push_back(I::ModelInfoClient->GetModelIndex("models/items/ammopack_medium.mdl"));
		m_vecAmmo.push_back(I::ModelInfoClient->GetModelIndex("models/items/ammopack_small.mdl"));
	}

	m_vecHealth.clear();
	{
		m_vecHealth.push_back(I::ModelInfoClient->GetModelIndex("models/items/medkit_large.mdl"));
		m_vecHealth.push_back(I::ModelInfoClient->GetModelIndex("models/items/medkit_medium.mdl"));
		m_vecHealth.push_back(I::ModelInfoClient->GetModelIndex("models/items/medkit_small.mdl"));
		m_vecHealth.push_back(I::ModelInfoClient->GetModelIndex("models/items/medkit_overheal.mdl"));
	}

	m_mapPowerups.clear();
	{
		m_mapPowerups.emplace(I::ModelInfoClient->GetModelIndex("models/pickups/pickup_powerup_crit.mdl"), L"POWERUP_CRIT");
		m_mapPowerups.emplace(I::ModelInfoClient->GetModelIndex("models/pickups/pickup_powerup_invis.mdl"), L"POWERUP_INVIS");
		m_mapPowerups.emplace(I::ModelInfoClient->GetModelIndex("models/pickups/pickup_powerup_defense.mdl"), L"POWERUP_SHIELD");
		m_mapPowerups.emplace(I::ModelInfoClient->GetModelIndex("models/pickups/pickup_powerup_knockout.mdl"), L"POWERUP_BERSERK");
		m_mapPowerups.emplace(I::ModelInfoClient->GetModelIndex("models/pickups/pickup_powerup_haste.mdl"), L"POWERUP_HASTE");
		m_mapPowerups.emplace(I::ModelInfoClient->GetModelIndex("models/pickups/pickup_powerup_megahealth.mdl"), L"POWERUP_MEGAHEALTH");
	}
}

bool CFeatures_ESP::IsAmmo(const int nModelIndex)
{
	size_t n; const size_t nMax = m_vecAmmo.size();
	for (n = 0; n < nMax; n++)
	{
		if (m_vecAmmo[n] == nModelIndex)
			return true;
	}

	return false;
}

bool CFeatures_ESP::IsHealth(const int nModelIndex)
{
	size_t n; const size_t nMax = m_vecHealth.size();
	for (n = 0; n < nMax; n++)
	{
		if (m_vecHealth[n] == nModelIndex)
			return true;
	}

	return false;
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