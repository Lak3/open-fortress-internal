#pragma once

#include "client_class.h"
#include "bspflags.h"

class bf_write
{
public:
	void StartWriting(void* pData, int nBytes, int iStartBit = 0, int nMaxBits = -1)
	{
		nBytes &= ~3;

		m_pData = (unsigned long*)pData;
		m_nDataBytes = nBytes;

		if (nMaxBits == -1)
		{
			m_nDataBits = nBytes << 3;
		}

		else
		{
			m_nDataBits = nMaxBits;
		}

		m_iCurBit = iStartBit;
		m_bOverflow = false;
	}

public:
	unsigned long* __restrict m_pData;
	int m_nDataBytes;
	int m_nDataBits;
	int m_iCurBit;
	bool m_bOverflow;
	bool m_bAssertOnOverflow;
	const char* m_pDebugName;
};

class bf_read
{
public:
	const unsigned char* m_pData;
	int m_nDataBytes;
	int m_nDataBits;
	int m_iCurBit;
	bool m_bOverflow;
	bool m_bAssertOnOverflow;
	const char* m_pDebugName;
};