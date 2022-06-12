#pragma once

#include "AnalogCode.h"

class IVguiMatInfoVar
{
public:
	virtual ~IVguiMatInfoVar() {}
	virtual int GetIntValue(void) const = 0;
	virtual void SetIntValue(int val) = 0;
};