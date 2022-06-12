#pragma once

#include "IClientNetworkable.h"

class CMouthInfo;
struct SpatializationInfo_t;

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual void Release(void) = 0;
	virtual const Vector& GetAbsOrigin(void) const = 0;
	virtual const Vector& GetAbsAngles(void) const = 0;
	virtual CMouthInfo* GetMouth(void) = 0;
	virtual bool GetSoundSpatialization(SpatializationInfo_t& info) = 0;

	template <typename T>
	inline T As()
	{
#ifdef _DEBUG
		return dynamic_cast<T>(this);
#else
		return static_cast<T>(this);
#endif
	}
};