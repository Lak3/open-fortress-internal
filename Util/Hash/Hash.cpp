#include "Hash.h"

//Slooooow
int CUtil_Hash::String(const char* szOrg)
{
	int iHash = 5381;

	while (int iStr = *szOrg++)
		iHash = iHash * 33 + iStr;

	return iHash;
}