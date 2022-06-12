#pragma once

#include "C_BaseAnimatingOverlay.h"

class CSceneEventInfo;
class CChoreoActor;
class CChoreoScene;
class CChoreoEvent;

class IHasLocalToGlobalFlexSettings
{
public:
	virtual void EnsureTranslations(const void* pSettinghdr) = 0;
};

class C_BaseFlex : public C_BaseAnimatingOverlay, public IHasLocalToGlobalFlexSettings
{
public:
	virtual			~C_BaseFlex() = 0;

	virtual void	InitPhonemeMappings() = 0;
	virtual	bool	SetupGlobalWeights(const matrix3x4_t* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights) = 0;
	virtual	void	SetupLocalWeights(const matrix3x4_t* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights) = 0;
	virtual Vector	SetViewTarget(CStudioHdr* pStudioHdr) = 0;
	virtual bool	StartSceneEvent(CSceneEventInfo* info, CChoreoScene* scene, CChoreoEvent* event, CChoreoActor* actor, C_BaseEntity* pTarget) = 0;
	virtual void	ProcessSceneEvents(bool bFlexEvents) = 0;
	virtual	bool	ProcessSceneEvent(bool bFlexEvents, CSceneEventInfo* info, CChoreoScene* scene, CChoreoEvent* event) = 0;
	virtual bool	ProcessSequenceSceneEvent(CSceneEventInfo* info, CChoreoScene* scene, CChoreoEvent* event) = 0;
	virtual	bool	ClearSceneEvent(CSceneEventInfo* info, bool fastKill, bool canceled) = 0;
	virtual bool	CheckSceneEventCompletion(CSceneEventInfo* info, float currenttime, CChoreoScene* scene, CChoreoEvent* event) = 0;
	virtual void	EnsureTranslations(const void* pSettinghdr) = 0;

public:
	NETVAR(m_flexWeight, void*, "CBaseFlex", "m_flexWeight");
	NETVAR(m_blinktoggle, bool, "CBaseFlex", "m_blinktoggle");
	NETVAR(m_viewtarget, Vector, "CBaseFlex", "m_viewtarget");
};