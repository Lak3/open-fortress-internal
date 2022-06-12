#pragma once

#include "basetypes.h"

typedef struct _XUSER_DATA
{
	BYTE type;

	union
	{
		int nData;
		int64 i64Data;
		double dblData;
		struct
		{
			uint cbData;
			char* pwszData;
		} string;
		float fData;
		struct
		{
			uint cbData;
			char* pbData;
		} binary;
	};
} XUSER_DATA, * PXUSER_DATA;

typedef struct _XUSER_PROPERTY
{
	DWORD dwPropertyId;
	XUSER_DATA value;
} XUSER_PROPERTY, * PXUSER_PROPERTY;

typedef struct _XUSER_CONTEXT
{
	DWORD dwContextId;
	DWORD dwValue;
} XUSER_CONTEXT, * PXUSER_CONTEXT;