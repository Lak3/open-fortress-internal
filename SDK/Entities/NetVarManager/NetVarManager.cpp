#include "NetVarManager.h"

int CHelpers_NetVarManager::Get(const char* const szClass, const char* const szVarName)
{
	ClientClass* pCC = I::BaseClientDLL->GetAllClasses();

	while (pCC)
	{
		if (HASH_RT(szClass) == HASH_RT(pCC->m_pNetworkName))
			return GetOffset(pCC->m_pRecvTable, szVarName);

		pCC = pCC->m_pNext;
	}

	return 0;
}

int CHelpers_NetVarManager::GetOffset(RecvTable* pTable, const char* const szVarName)
{
	int n;
	for (n = 0; n < pTable->m_nProps; n++)
	{
		RecvProp Prop = pTable->m_pProps[n];

		if (HASH_RT(Prop.m_pVarName) == HASH_RT(szVarName))
			return Prop.GetOffset();

		RecvTable* pTable = Prop.GetDataTable();

		if (pTable)
		{
			const int nOff = GetOffset(pTable, szVarName);

			if (nOff)
				return (nOff + Prop.GetOffset());
		}
	}

	return 0;
}