#pragma once

#include "C_TFPlayer.h"

class C_BaseSchemaEntity : public C_BaseAnimating
{
public:
	virtual ~C_BaseSchemaEntity() = 0;

public:
	NETVAR(m_iszSchemaName, const char*, "CBaseSchemaEntity", "m_iszSchemaName");
};