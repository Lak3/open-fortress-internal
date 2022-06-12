#pragma once

#include "dt_recv.h"

class IClientNetworkable;
class CSaveRestoreData;

typedef IClientNetworkable* (*CreateClientClassFn)(int entnum, int serialNum);
typedef IClientNetworkable* (*CreateEventFn)();

class ClientClass
{
public:
	CreateClientClassFn	m_pCreateFn;
	CreateEventFn m_pCreateEventFn;
	const char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int m_ClassID;

	const char* GetName() { return m_pNetworkName; }
};

class CGlobalVarsBase
{
public:
	float realtime;
	int framecount;
	float absoluteframetime;
	float curtime;
	float frametime;
	int maxClients;
	int tickcount;
	float interval_per_tick;
	float interpolation_amount;
	int simTicksThisFrame;
	int network_protocol;
	CSaveRestoreData* pSaveData;
	bool m_bClient;
	int nTimestampNetworkingBase;
	int nTimestampRandomizeWindow;
};

namespace I { inline CGlobalVarsBase* GlobalVarsBase = nullptr; }

#define TICK_INTERVAL			(I::GlobalVarsBase->interval_per_tick)
#define TIME_TO_TICKS( dt )		( static_cast<int>( 0.5f + static_cast<float>(dt) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )		( TICK_INTERVAL * ( t ) )
#define ROUND_TO_TICKS( t )		( TICK_INTERVAL * TIME_TO_TICKS( t ) )
#define TICK_NEVER_THINK		(-1)