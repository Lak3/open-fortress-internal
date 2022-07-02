#pragma once

#include "IClientEntity.h"

class C_BaseEntity;
class ITraceFilter;
class CTakeDamageInfo;
class CDmgAccumulator;
class CEntityMapData;
class C_BaseAnimating;
class IPhysicsObject;
class C_Team;
class IClientVehicle;
class CStudioHdr;
class CNewParticleEffect;
class CDamageModifier;
class C_BaseCombatCharacter;

enum FireBulletsFlags_t
{
	FIRE_BULLETS_FIRST_SHOT_ACCURATE = 0x1,		// Pop the first shot with perfect accuracy
	FIRE_BULLETS_DONT_HIT_UNDERWATER = 0x2,		// If the shot hits its target underwater, don't damage it
	FIRE_BULLETS_ALLOW_WATER_SURFACE_IMPACTS = 0x4,	// If the shot hits water surface, still call DoImpactEffect
	FIRE_BULLETS_TEMPORARY_DANGER_SOUND = 0x8,		// Danger sounds added from this impact can be stomped immediately if another is queued
};

enum CollideType_t
{
	ENTITY_SHOULD_NOT_COLLIDE = 0,
	ENTITY_SHOULD_COLLIDE,
	ENTITY_SHOULD_RESPOND
};

struct FireBulletsInfo_t
{
	int m_iShots;
	Vector m_vecSrc;
	Vector m_vecDirShooting;
	Vector m_vecSpread;
	float m_flDistance;
	int m_iAmmoType;
	int m_iTracerFreq;
	float m_flDamage;
	int m_iPlayerDamage;	// Damage to be used instead of m_flDamage if we hit a player
	int m_nFlags;			// See FireBulletsFlags_t
	float m_flDamageForceScale;
	C_BaseEntity* m_pAttacker;
	C_BaseEntity* m_pAdditionalIgnoreEnt;
	bool m_bPrimaryAttack;
	bool m_bUseServerRandomSeed;
};

class C_BaseEntity : public IClientEntity
{
public:
	enum thinkmethods_t
	{
		THINK_FIRE_ALL_FUNCTIONS,
		THINK_FIRE_BASE_ONLY,
		THINK_FIRE_ALL_BUT_BASE,
	};

public:
	virtual						~C_BaseEntity() = 0;

	virtual void*				GetDataDescMap() = 0; //datamap_t*
	virtual void*				YouForgotToImplementOrDeclareClientClass() = 0;
	virtual void*				GetPredDescMap() = 0; //datamap_t*

	virtual void				FireBullets(const FireBulletsInfo_t& info) = 0;
	virtual void				ModifyFireBulletsDamage(CTakeDamageInfo* dmgInfo) = 0;
	virtual bool				ShouldDrawWaterImpacts(void) = 0;
	virtual bool				HandleShotImpactingWater(const FireBulletsInfo_t& info, const Vector& vecEnd, ITraceFilter* pTraceFilter, Vector* pVecTracerDest) = 0;
	virtual ITraceFilter*		GetBeamTraceFilter(void) = 0;
	virtual void				DispatchTraceAttack(const CTakeDamageInfo& info, const Vector& vecDir, trace_t* ptr, CDmgAccumulator* pAccumulator = NULL) = 0;
	virtual void				TraceAttack(const CTakeDamageInfo& info, const Vector& vecDir, trace_t* ptr, CDmgAccumulator* pAccumulator = NULL) = 0;
	virtual void				DoImpactEffect(trace_t& tr, int nDamageType) = 0;
	virtual void				MakeTracer(const Vector& vecTracerSrc, const trace_t& tr, int iTracerType) = 0;
	virtual int					GetTracerAttachment(void) = 0;
	virtual int					BloodColor() = 0;
	virtual const char*			GetTracerType() = 0;
	virtual void				Spawn(void) = 0;
	virtual void				SpawnClientEntity(void) = 0;
	virtual void				Precache(void) = 0;
	virtual void				Activate() = 0;
	virtual void				ParseMapData(CEntityMapData* mapData) = 0;
	virtual bool				KeyValue(const char* szKeyName, const char* szValue) = 0;
	virtual bool				KeyValue(const char* szKeyName, float flValue) = 0;
	virtual bool				KeyValue(const char* szKeyName, const Vector& vecValue) = 0;
	virtual bool				GetKeyValue(const char* szKeyName, char* szValue, int iMaxLen) = 0;
	virtual bool				Init(int entnum, int iSerialNum) = 0;
	virtual C_BaseAnimating*	GetBaseAnimating() = 0;
	virtual void				SetClassname(const char* className) = 0;
	virtual void				SetKillIcon(char const* unk1) = 0;
	virtual void				RecordToolMessage() = 0;
	virtual Vector				GetObserverCamOrigin(void) = 0;
	virtual const matrix3x4_t&  RenderableToWorldTransform() = 0;
	virtual bool				IsTransparent(void) = 0;
	virtual bool				IsTwoPass(void) = 0;
	virtual bool				UsesPowerOfTwoFrameBufferTexture() = 0;
	virtual bool				UsesFullFrameBufferTexture() = 0;
	virtual bool				IgnoresZBuffer(void) const = 0;
	virtual bool				TestCollision(const Ray_t& ray, unsigned int fContentsMask, trace_t& tr) = 0;
	virtual bool				TestHitboxes(const Ray_t& ray, unsigned int fContentsMask, trace_t& tr) = 0;
	virtual float				GetAttackDamageScale(void) = 0;
	virtual void				ValidateModelIndex(void) = 0;
	virtual void				SetDormant(bool bDormant) = 0;
	virtual int				    GetEFlags() const = 0;
	virtual void			    SetEFlags(int iEFlags) = 0;
	virtual bool				ShouldSavePhysics() = 0;
	virtual void				OnSave() = 0;
	virtual void				OnRestore() = 0;
	virtual int					ObjectCaps(void) = 0;
	virtual int					Save(void* save) = 0;
	virtual int					Restore(void* restore) = 0;
	virtual bool	            CreateVPhysics() = 0;
	virtual void	            VPhysicsDestroyObject(void) = 0;
	virtual void				VPhysicsUpdate(IPhysicsObject* pPhysics) = 0;
	virtual int					VPhysicsGetObjectList(IPhysicsObject** pList, int listMax) = 0;
	virtual bool				VPhysicsIsFlesh(void) = 0;
	virtual void				AddEntity(void) = 0;
	virtual const Vector&       GetPrevLocalOrigin() const = 0;
	virtual const Vector&       GetPrevLocalAngles() const = 0;
	virtual int					CalcOverrideModelIndex() = 0;
	virtual const Vector&		WorldAlignMins() const = 0;
	virtual const Vector&		WorldAlignMaxs() const = 0;
	virtual const Vector&		WorldSpaceCenter() const = 0;
	virtual void				ComputeWorldSpaceSurroundingBox(Vector* pVecWorldMins, Vector* pVecWorldMaxs) = 0;

private:
	//C_BaseEntity::GetHealthBarHeightOffset(void)const
	virtual void*               GetHealthBarHeightOffset(void) const = 0;

public:
	virtual SolidType_t			GetSolid(void) const = 0;
	virtual int			 		GetSolidFlags(void) const = 0;
	virtual int					LookupAttachment(const char* pAttachmentName) = 0;
	virtual bool				GetAttachment(int number, matrix3x4_t& matrix) = 0;
	virtual bool				GetAttachment(int number, Vector& origin) = 0;
	virtual	bool				GetAttachment(int number, Vector& origin, Vector& angles) = 0;
	virtual bool				GetAttachmentVelocity(int number, Vector& originVel, Quaternion& angleVel) = 0;
	virtual C_Team*             GetTeam(void) = 0;
	virtual int					GetTeamNumber(void) const = 0;
	virtual void				ChangeTeam(int iTeamNum) = 0;
	virtual int					GetRenderTeamNumber(void) = 0;
	virtual bool				InSameTeam(C_BaseEntity* pEntity) = 0;
	virtual bool				InLocalTeam(void) = 0;
	virtual bool				IsValidIDTarget(void) = 0;
	virtual const char*			GetIDString(void) = 0;
	virtual void				ModifyEmitSoundParams(void* params) = 0; //EmitSound_t& params
	virtual bool                InitializeAsClientEntity(const char* pszModelName, int renderGroup) = 0;
	virtual void				Simulate() = 0;
	virtual IClientVehicle*     GetClientVehicle() = 0;
	virtual void				GetAimEntOrigin(IClientEntity* pAttachedTo, Vector* pAbsOrigin, Vector* pAbsAngles) = 0;
	virtual const Vector&		GetOldOrigin() = 0;
	virtual int					GetRenderGroup() = 0;
	virtual void				GetToolRecordingState(KeyValues* msg) = 0;
	virtual void				CleanupToolRecordingState(KeyValues* msg) = 0;
	virtual CollideType_t		GetCollideType(void) = 0;
	virtual void				UpdateVisibility() = 0;
	virtual bool				IsSelfAnimating() = 0;
	virtual	void				OnLatchInterpolatedVariables(int flags) = 0;
	virtual CStudioHdr*			OnNewModel() = 0;
	virtual void				OnNewParticleEffect(const char* pszParticleName, CNewParticleEffect* pNewParticleEffect) = 0;
	virtual void				ResetLatched() = 0;
	virtual bool				Interpolate(float currentTime) = 0;
	virtual bool				IsSubModel(void) = 0;
	virtual void				CreateLightEffects(void) = 0;
	virtual void				Clear(void) = 0;
	virtual int					DrawBrushModel(bool bTranslucent, int nFlags, bool bTwoPass) = 0;
	virtual float				GetTextureAnimationStartTime() = 0;
	virtual void				TextureAnimationWrapped() = 0;
	virtual void				SetNextClientThink(float nextThinkTime) = 0;
	virtual void				SetHealth(int iHealth) = 0;
	virtual int					GetHealth() const = 0;
	virtual int					GetMaxHealth() const = 0;
	virtual bool				IsVisibleToTargetID(void) = 0;
	virtual bool                IsHealthBarVisible(void) const = 0;
	virtual void				AddDecal(const Vector& rayStart, const Vector& rayEnd, const Vector& decalCenter, int hitbox, int decalIndex, bool doTrace, trace_t& tr, int maxLODToDecal) = 0;
	virtual void				AddColoredDecal(const Vector& rayStart, const Vector& rayEnd, const Vector& decalCenter, int hitbox, int decalIndex, bool doTrace, trace_t& tr, Color cColor, int maxLODToDecal) = 0;
	virtual bool				IsClientCreated(void) const = 0;
	virtual void				UpdateOnRemove(void) = 0;
	virtual void				SUB_Remove(void) = 0;
	virtual void				SetPredictable(bool state) = 0;
	virtual int				    RestoreData(const char* context, int slot, int type) = 0;
	virtual char const*         DamageDecal(int bitsDamageType, int gameMaterial) = 0;
	virtual void				DecalTrace(trace_t* pTrace, char const* decalName) = 0;
	virtual void				ImpactTrace(trace_t* pTrace, int iDamageType, const char* pCustomImpactName) = 0;
	virtual bool				ShouldPredict(void) = 0;
	virtual void				Think(void) = 0;
	virtual bool				CanBePoweredUp(void) = 0;
	virtual bool				AttemptToPowerup(int iPowerup, float flTime, float flAmount = 0, C_BaseEntity* pAttacker = NULL, CDamageModifier* pDamageModifier = NULL) = 0;
	virtual bool                IsCurrentlyTouching(void)const = 0;
	virtual void				StartTouch(C_BaseEntity* pOther) = 0;
	virtual void				Touch(C_BaseEntity* pOther) = 0;
	virtual void				EndTouch(C_BaseEntity* pOther) = 0;
	virtual unsigned int	    PhysicsSolidMaskForEntity(void) const = 0;
	virtual void				PhysicsSimulate(void) = 0;
	virtual bool				IsAlive(void) = 0;
	virtual bool				IsPlayer(void) const = 0;
	virtual bool			    IsBaseCombatCharacter(void) = 0;
	virtual C_BaseCombatCharacter* MyCombatCharacterPointer(void) = 0;
	virtual bool				IsNPC(void) = 0;
	virtual bool				IsNextBot() = 0;
	virtual bool				IsBaseObject(void) const = 0;
	virtual bool				IsBaseCombatWeapon(void) const = 0;
	virtual class C_BaseCombatWeapon* MyCombatWeaponPointer() = 0;
	virtual bool				IsCombatItem(void) const = 0;
	virtual bool				IsBaseTrain(void) const = 0;
	virtual void                OnAirblast(C_BaseEntity* pUnk1) = 0;
	virtual Vector				EyePosition(void) = 0;
	virtual const Vector&		EyeAngles(void) = 0;
	virtual const Vector&		LocalEyeAngles(void) = 0;
	virtual Vector				EarPosition(void) = 0;
	virtual bool				ShouldCollide(int collisionGroup, int contentsMask, C_BaseEntity* pUnk1) const = 0;
	virtual bool				ShouldCollide(int collisionGroup, int contentsMask) const = 0;
	virtual const Vector&		GetViewOffset() const = 0;
	virtual void				SetViewOffset(const Vector& v) = 0;
	virtual bool                ShouldInterpolate() = 0;
	virtual unsigned char       GetClientSideFade() = 0;
	virtual void				BoneMergeFastCullBloat(Vector& localMins, Vector& localMaxs, const Vector& thisEntityMins, const Vector& thisEntityMaxs) const = 0;
	virtual bool				OnPredictedEntityRemove(bool isbeingremoved, C_BaseEntity* predicted) = 0;
	virtual C_BaseEntity*		GetShadowUseOtherEntity(void) const = 0;
	virtual void				SetShadowUseOtherEntity(C_BaseEntity* pEntity) = 0;
	virtual bool				AddRagdollToFadeQueue(void) = 0;
	virtual bool				IsDeflectable() = 0;
	virtual int					GetStudioBody(void) = 0;
	virtual void				PerformCustomPhysics(Vector* pNewPosition, Vector* pNewVelocity, Vector* pNewAngles, Vector* pNewAngVelocity) = 0;
	virtual float*              GetRenderClipPlane(void) = 0;

private:
	//C_BaseEntity::GetItemTintColor(void)
	virtual void* GetItemTintColor(void) = 0;

	//C_BaseEntity::GetItemTintColorOwner(void)
	virtual void* GetItemTintColorOwner(void) = 0;

public:
	static void SetPredictionRandomSeed(const CUserCmd* cmd) {
		reinterpret_cast<void(*)(const CUserCmd*)>(U::Offsets.m_dwC_BaseEntity_SetPredictionRandomSeed)(cmd);
	}

	static void SetPredictionPlayer(C_BasePlayer* player) {
		static const DWORD s_dwOff = (reinterpret_cast<DWORD>(GetModuleHandleW(L"client.dll")) + 0x105C1F18); //Epic hardcoded shit

		*reinterpret_cast<C_BasePlayer**>(s_dwOff) = player;
	}

	static C_BaseEntity* Instance(const int iEnt) {
		return reinterpret_cast<C_BaseEntity* (*)(int)>(U::Offsets.m_dwC_BaseEntity_Instance)(iEnt);
	}

public:
	NETVAR(m_flAnimTime, int, "CBaseEntity", "m_flAnimTime");
	NETVAR(m_flSimulationTime, int, "CBaseEntity", "m_flSimulationTime");
	NETVAR(m_ubInterpolationFrame, int, "CBaseEntity", "m_ubInterpolationFrame");
	NETVAR(m_vecOrigin, Vector, "CBaseEntity", "m_vecOrigin");
	NETVAR(m_angRotation, Vector, "CBaseEntity", "m_angRotation");
	NETVAR(m_nModelIndex, int, "CBaseEntity", "m_nModelIndex");
	NETVAR(m_fEffects, int, "CBaseEntity", "m_fEffects");
	NETVAR(m_nRenderMode, int, "CBaseEntity", "m_nRenderMode");
	NETVAR(m_nRenderFX, int, "CBaseEntity", "m_nRenderFX");
	NETVAR(m_clrRender, int, "CBaseEntity", "m_clrRender");
	NETVAR(m_iTeamNum, int, "CBaseEntity", "m_iTeamNum");
	NETVAR(m_CollisionGroup, int, "CBaseEntity", "m_CollisionGroup");
	NETVAR(m_flElasticity, float, "CBaseEntity", "m_flElasticity");
	NETVAR(m_flShadowCastDistance, float, "CBaseEntity", "m_flShadowCastDistance");
	NETVAR(m_hOwnerEntity, int, "CBaseEntity", "m_hOwnerEntity");
	NETVAR(m_hEffectEntity, int, "CBaseEntity", "m_hEffectEntity");
	NETVAR(moveparent, int, "CBaseEntity", "moveparent");
	NETVAR(m_iParentAttachment, int, "CBaseEntity", "m_iParentAttachment");
	NETVAR(m_vecAttachmentOffset, Vector, "CBaseEntity", "m_vecAttachmentOffset");
	NETVAR(m_Collision, void*, "CBaseEntity", "m_Collision");
	NETVAR(m_vecMinsPreScaled, Vector, "CBaseEntity", "m_vecMinsPreScaled");
	NETVAR(m_vecMaxsPreScaled, Vector, "CBaseEntity", "m_vecMaxsPreScaled");
	NETVAR(m_vecMins, Vector, "CBaseEntity", "m_vecMins");
	NETVAR(m_vecMaxs, Vector, "CBaseEntity", "m_vecMaxs");
	NETVAR(m_nSolidType, int, "CBaseEntity", "m_nSolidType");
	NETVAR(m_usSolidFlags, int, "CBaseEntity", "m_usSolidFlags");
	NETVAR(m_nSurroundType, int, "CBaseEntity", "m_nSurroundType");
	NETVAR(m_triggerBloat, int, "CBaseEntity", "m_triggerBloat");
	NETVAR(m_vecSpecifiedSurroundingMinsPreScaled, Vector, "CBaseEntity", "m_vecSpecifiedSurroundingMinsPreScaled");
	NETVAR(m_vecSpecifiedSurroundingMaxsPreScaled, Vector, "CBaseEntity", "m_vecSpecifiedSurroundingMaxsPreScaled");
	NETVAR(m_vecSpecifiedSurroundingMins, Vector, "CBaseEntity", "m_vecSpecifiedSurroundingMins");
	NETVAR(m_vecSpecifiedSurroundingMaxs, Vector, "CBaseEntity", "m_vecSpecifiedSurroundingMaxs");
	NETVAR(m_iTextureFrameIndex, int, "CBaseEntity", "m_iTextureFrameIndex");
	NETVAR(m_PredictableID, int, "CBaseEntity", "m_PredictableID");
	NETVAR(m_bIsPlayerSimulated, bool, "CBaseEntity", "m_bIsPlayerSimulated");
	NETVAR(m_bSimulatedEveryTick, bool, "CBaseEntity", "m_bSimulatedEveryTick");
	NETVAR(m_bAnimatedEveryTick, bool, "CBaseEntity", "m_bAnimatedEveryTick");
	NETVAR(m_bAlternateSorting, bool, "CBaseEntity", "m_bAlternateSorting");
	NETVAR(m_szKillIcon, const char*, "CBaseEntity", "m_szKillIcon");
};

typedef CHandle<C_BaseEntity> EHANDLE; // The client's version of EHANDLE.