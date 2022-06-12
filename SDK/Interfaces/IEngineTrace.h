#pragma once

#include "IGameEventManager.h"

class CTraceListData;
class ICollideable;

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(IHandleEntity* pEntity, int contentsMask) = 0;
	virtual TraceType_t	GetTraceType() const = 0;
};

class CTraceFilter : public ITraceFilter
{
public:
	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}
};

class CTraceFilterEntitiesOnly : public ITraceFilter
{
public:
	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_ENTITIES_ONLY;
	}
};

class CTraceFilterWorldOnly : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pServerEntity, int contentsMask)
	{
		return false;
	}

	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_WORLD_ONLY;
	}
};

class CTraceFilterWorldAndPropsOnly : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pServerEntity, int contentsMask)
	{
		return false;
	}

	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}
};

class CTraceFilterHitAll : public CTraceFilter
{
public:
	virtual bool ShouldHitEntity(IHandleEntity* pServerEntity, int contentsMask)
	{
		return true;
	}
};

class IEntityEnumerator
{
public:
	virtual bool EnumEntity(IHandleEntity* pHandleEntity) = 0;
};

class IEngineTrace
{
public:
	virtual int	GetPointContents(const Vector& vecAbsPosition, IHandleEntity** ppEntity = NULL) = 0;
	virtual int	GetPointContents_Collideable(ICollideable* pCollide, const Vector& vecAbsPosition) = 0;
	virtual void ClipRayToEntity(const Ray_t& ray, unsigned int fMask, IHandleEntity* pEnt, trace_t* pTrace) = 0;
	virtual void ClipRayToCollideable(const Ray_t& ray, unsigned int fMask, ICollideable* pCollide, trace_t* pTrace) = 0;
	virtual void TraceRay(const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace) = 0;
	virtual void SetupLeafAndEntityListRay(const Ray_t& ray, CTraceListData& traceData) = 0;
	virtual void SetupLeafAndEntityListBox(const Vector& vecBoxMin, const Vector& vecBoxMax, CTraceListData& traceData) = 0;
	virtual void TraceRayAgainstLeafAndEntityList(const Ray_t& ray, CTraceListData& traceData, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace) = 0;
	virtual void SweepCollideable(ICollideable* pCollide, const Vector& vecAbsStart, const Vector& vecAbsEnd, const Vector& vecAngles, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace) = 0;
	virtual void EnumerateEntities(const Ray_t& ray, bool triggers, IEntityEnumerator* pEnumerator) = 0;
	virtual void EnumerateEntities(const Vector& vecAbsMins, const Vector& vecAbsMaxs, IEntityEnumerator* pEnumerator) = 0;
	virtual ICollideable* GetCollideable(IHandleEntity* pEntity) = 0;
	virtual int GetStatByIndex(int index, bool bClear) = 0;
	virtual void GetBrushesInAABB(const Vector& vMins, const Vector& vMaxs, CUtlVector<int>* pOutput, int iContentsMask = 0xFFFFFFFF) = 0;
	virtual CPhysCollide* GetCollidableFromDisplacementsInAABB(const Vector& vMins, const Vector& vMaxs) = 0;

private:
	//virtual bool GetBrushInfo(int iBrush, CUtlVector<Vector4D>* pPlanesOut, int* pContentsOut) = 0;
	virtual void* KuljuHonorPad() = 0;

public:
	virtual bool PointOutsideWorld(const Vector& ptTest) = 0;
	virtual int GetLeafContainingPoint(const Vector& ptTest) = 0;
};

namespace I { inline IEngineTrace* EngineTraceClient = nullptr; }