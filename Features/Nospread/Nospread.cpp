#include "Nospread.h"

void CFeatures_Nospread::Think(CUserCmd* pCommand)
{
	static const auto s_pfSharedRandomInt = reinterpret_cast<int(*)(const char*, int, int, int)>(U::Offsets.m_dwSharedRandomInt);
	static const auto s_pfRandomSeed      = reinterpret_cast<void(_cdecl*)(unsigned)>(GetProcAddress(GetModuleHandleW(L"vstdlib.dll"), "RandomSeed"));
	static const auto s_pfRandomFloat     = reinterpret_cast<float(_cdecl*)(float, float)>(GetProcAddress(GetModuleHandleW(L"vstdlib.dll"), "RandomFloat"));

	C_TFPlayer* pLocal = C_BaseEntity::Instance(I::EngineClient->GetLocalPlayer())->As<C_TFPlayer*>();

	if (!pLocal || !pLocal->IsAlive())
		return;

	C_BaseCombatWeapon* pBaseWeapon = pLocal->GetActiveWeapon();

	if (!pBaseWeapon || !pBaseWeapon->HasAnyAmmo())
		return;

	C_TFWeaponBase* pTFWeapon = pBaseWeapon->As<C_TFWeaponBase*>();

	if (!pTFWeapon)
		return;

	const int nWeaponID = pTFWeapon->GetWeaponID();

	if (IsNeedleGun(nWeaponID))
	{
		s_pfSharedRandomInt("SelectWeightedSequence", 0, 0, 0);

		int n;
		for (n = 0; n < 6; n++)
			s_pfRandomFloat(-1, 1);

		Vector vSpread =
		{
			(pCommand->viewangles.x - s_pfRandomFloat(-1.5f, 1.5f)),
			(pCommand->viewangles.y - s_pfRandomFloat(-1.5f, 1.5f)),
			0.0f
		};
		U::Math.ClampAngles(vSpread);

		pCommand->viewangles = vSpread;
	}
	else if (CanWeaponNospread(nWeaponID))
	{
		C_TFWeaponBaseGun* pTFGun = pTFWeapon->As<C_TFWeaponBaseGun*>();

		if (!pTFGun)
			return;

		Vector vForward, vRight, vUp, vFinal;

		U::Math.ClampAngles(pCommand->viewangles);

		s_pfRandomSeed((pCommand->random_seed & 255));

		const float flX = (s_pfRandomFloat(-0.5f, 0.5f) + s_pfRandomFloat(-0.5f, 0.5f));
		const float flY = (s_pfRandomFloat(-0.5f, 0.5f) + s_pfRandomFloat(-0.5f, 0.5f));
		const float flSpread = (pTFGun->GetWeaponSpread());

		U::Math.AngleVectors(pCommand->viewangles, &vForward, &vRight, &vUp);

		Vector vNewAngles = vForward + (vRight * (flX * flSpread)) + (vUp * (flY * flSpread));
		vNewAngles.Normalize();

		U::Math.VectorAngles(vNewAngles, vFinal);
		U::Math.ClampAngles(vFinal);

		Vector vSpreadAngles = (pCommand->viewangles + (pCommand->viewangles - vFinal));
		U::Math.ClampAngles(vSpreadAngles);

		pCommand->viewangles = vSpreadAngles;
	}
}

bool CFeatures_Nospread::CanWeaponNospread(const int nWeaponID)
{
	return Util::CompareGroup(nWeaponID, TF_WEAPON_ASSAULTRIFLE, TF_WEAPON_SMG, TF_WEAPON_SMG_MERCENARY, TF_WEAPON_TOMMYGUN,
		TF_WEAPON_PISTOL, TF_WEAPON_PISTOL_MERCENARY, TF_WEAPON_PISTOL_AKIMBO, TF_WEAPON_REVOLVER_MERCENARY,
		TF_WEAPON_REVOLVER);
}

bool CFeatures_Nospread::IsNeedleGun(const int nWeaponID)
{
	return Util::CompareGroup(nWeaponID, TF_WEAPON_NAILGUN, TF_WEAPON_SYRINGEGUN_MEDIC);
}