#pragma once

#include "C_BaseEntity.h"

#define MAXSTUDIOPOSEPARAM 24
#define MAXSTUDIOBONECTRLS 4

class C_BaseAnimating : public C_BaseEntity, private IModelLoadCallback
{
public:
	virtual			~C_BaseAnimating() = 0;

	virtual void	GetBoneControllers(float controllers[MAXSTUDIOBONECTRLS]) = 0;
	virtual float	SetBoneController(int iController, float flValue) = 0;
	virtual void	GetPoseParameters(CStudioHdr* pStudioHdr, float poseParameter[MAXSTUDIOPOSEPARAM]) = 0;
	virtual void	BuildTransformations(CStudioHdr* pStudioHdr, Vector* pos, void* q, const matrix3x4_t& cameraTransform, int boneMask, void* boneComputed) = 0;
	virtual void	ApplyBoneMatrixTransform(matrix3x4_t& transform) = 0;
	virtual void	UpdateIKLocks(float currentTime) = 0;
	virtual void	CalculateIKLocks(float currentTime) = 0;
	virtual int		InternalDrawModel(int flags) = 0;
	virtual bool	OnInternalDrawModel(void* pInfo) = 0;
	virtual bool	OnPostInternalDrawModel(void* pInfo) = 0;
	virtual void	ControlMouth(CStudioHdr* pStudioHdr) = 0;
	virtual void	DoAnimationEvents(CStudioHdr* pStudio) = 0;
	virtual void	FireEvent(const Vector& origin, const Vector& angles, int event, const char* options) = 0;
	virtual void	FireObsoleteEvent(const Vector& origin, const Vector& angles, int event, const char* options) = 0;
	virtual const char* ModifyEventParticles(const char* token) = 0;
	virtual bool	DispatchMuzzleEffect(const char* options, bool isFirstPerson) = 0;
	virtual	void	StandardBlendingRules(CStudioHdr* pStudioHdr, Vector pos[], void* q, float currentTime, int boneMask) = 0;
	virtual void	AccumulateLayers(void* boneSetup, Vector pos[], void* q, float currentTime) = 0;
	virtual void	ChildLayerBlend(Vector pos[], void* q, float currentTime, int boneMask) = 0;
	virtual void	AttachEntityToBone(C_BaseAnimating* attachTarget, int boneIndexAttached = -1, Vector bonePosition = Vector(0, 0, 0), Vector boneAngles = Vector(0, 0, 0)) = 0;
	virtual void	NotifyBoneAttached(C_BaseAnimating* attachTarget) = 0;
	virtual void	UpdateBoneAttachments(void) = 0;
	virtual C_BaseAnimating* BecomeRagdollOnClient() = 0;
	virtual void	SaveRagdollInfo(int numbones, const matrix3x4_t& cameraTransform, void* pBoneToWorld) = 0;
	virtual bool	RetrieveRagdollInfo(Vector* pos, void* q) = 0;
	virtual bool	GetRagdollInitBoneArrays(matrix3x4_t* pDeltaBones0, matrix3x4_t* pDeltaBones1, matrix3x4_t* pCurrentBones, float boneDt) = 0;
	virtual	void	RefreshCollisionBounds(void) = 0;
	virtual void	SetSequence(int nSequence) = 0;
	virtual void	StudioFrameAdvance() = 0;
	virtual float	FrameAdvance(float flInterval = 0.0f) = 0;
	virtual float	GetSequenceCycleRate(CStudioHdr* pStudioHdr, int iSequence) = 0;
	virtual void	UpdateClientSideAnimation() = 0;
	virtual unsigned int ComputeClientSideAnimationFlags() = 0;
	virtual void	GetGlowEffectColor(float* unk1, float* unk2, float* unk3) = 0; //r, g, b I assume.
	virtual void	ResetClientsideFrame(void) = 0;
	virtual bool	IsActivityFinished(void) = 0;
	virtual void	UncorrectViewModelAttachment(Vector& vOrigin) = 0;
	virtual void	DoMuzzleFlash() = 0;
	virtual void	ProcessMuzzleFlashEvent() = 0;
	virtual void	SetServerIntendedCycle(float intended) = 0;
	virtual float	GetServerIntendedCycle(void) = 0;
	virtual bool	ShouldResetSequenceOnNewModel(void) = 0;
	virtual bool	IsViewModel() const = 0;
	virtual void	FormatViewModelAttachment(int nAttachment, matrix3x4_t& attachmentToWorld) = 0;
	virtual bool	IsMenuModel() const = 0;
	virtual bool	CalcAttachments() = 0;
	virtual void	UpdateGlowEffect(void) = 0;
	virtual void	DestroyGlowEffect(void) = 0;
	virtual float	LastBoneChangedTime() = 0;
	virtual void	OnModelLoadComplete(const model_t* pModel) = 0;

public:
	inline bool GetHitboxPosition(const int nHitbox, Vector& vPosition)
	{
		const model_t* pModel = this->GetModel();

		if (!pModel)
			return false;

		const studiohdr_t* pStudioHdr = I::ModelInfoClient->GetStudiomodel(pModel);

		if (!pStudioHdr)
			return false;

		const mstudiobbox_t* pBox = pStudioHdr->pHitbox(nHitbox, this->m_nHitboxSet());

		if (!pBox || (pBox->bone >= MAXSTUDIOBONES) || (pBox->bone < 0))
			return false;

		matrix3x4_t Matrix[MAXSTUDIOBONES];
		if (!SetupBones(Matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, I::GlobalVarsBase->curtime))
			return false;

		U::Math.VectorTransform((pBox->bbmax + pBox->bbmin) * 0.5f, Matrix[pBox->bone], vPosition);
		return true;
	}

public:
	NETVAR(m_nSequence, int, "CBaseAnimating", "m_nSequence");
	NETVAR(m_nForceBone, int, "CBaseAnimating", "m_nForceBone");
	NETVAR(m_vecForce, Vector, "CBaseAnimating", "m_vecForce");
	NETVAR(m_nSkin, int, "CBaseAnimating", "m_nSkin");
	NETVAR(m_nBody, int, "CBaseAnimating", "m_nBody");
	NETVAR(m_nHitboxSet, int, "CBaseAnimating", "m_nHitboxSet");
	NETVAR(m_flModelScale, float, "CBaseAnimating", "m_flModelScale");
	NETVAR(m_flModelWidthScale, float, "CBaseAnimating", "m_flModelWidthScale");
	NETVAR(m_flPoseParameter, void*, "CBaseAnimating", "m_flPoseParameter");
	NETVAR(m_flPlaybackRate, float, "CBaseAnimating", "m_flPlaybackRate");
	NETVAR(m_flEncodedController, void*, "CBaseAnimating", "m_flEncodedController");
	NETVAR(m_bClientSideAnimation, bool, "CBaseAnimating", "m_bClientSideAnimation");
	NETVAR(m_bClientSideFrameReset, bool, "CBaseAnimating", "m_bClientSideFrameReset");
	NETVAR(m_nNewSequenceParity, int, "CBaseAnimating", "m_nNewSequenceParity");
	NETVAR(m_nResetEventsParity, int, "CBaseAnimating", "m_nResetEventsParity");
	NETVAR(m_nMuzzleFlashParity, int, "CBaseAnimating", "m_nMuzzleFlashParity");
	NETVAR(m_hLightingOrigin, int, "CBaseAnimating", "m_hLightingOrigin");
	NETVAR(m_hLightingOriginRelative, int, "CBaseAnimating", "m_hLightingOriginRelative");
	NETVAR(m_flCycle, float, "CBaseAnimating", "m_flCycle");
	NETVAR(m_fadeMinDist, float, "CBaseAnimating", "m_fadeMinDist");
	NETVAR(m_fadeMaxDist, float, "CBaseAnimating", "m_fadeMaxDist");
	NETVAR(m_flFadeScale, float, "CBaseAnimating", "m_flFadeScale");
	NETVAR(m_bGlowEnabled, bool, "CBaseAnimating", "m_bGlowEnabled");
};