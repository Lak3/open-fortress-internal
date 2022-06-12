#pragma once

#include "IBaseClientDll.h"

#define FCVAR_NONE 0 
#define FCVAR_UNREGISTERED (1<<0)
#define FCVAR_DEVELOPMENTONLY (1<<1)
#define FCVAR_GAMEDLL (1<<2)
#define FCVAR_CLIENTDLL (1<<3)
#define FCVAR_HIDDEN (1<<4)
#define FCVAR_PROTECTED (1<<5)
#define FCVAR_SPONLY (1<<6)
#define	FCVAR_ARCHIVE (1<<7)
#define	FCVAR_NOTIFY (1<<8)
#define	FCVAR_USERINFO (1<<9)
#define FCVAR_CHEAT (1<<14)
#define FCVAR_PRINTABLEONLY (1<<10)
#define FCVAR_UNLOGGED (1<<11)
#define FCVAR_NEVER_AS_STRING (1<<12)
#define FCVAR_REPLICATED (1<<13)
#define FCVAR_DEMO (1<<16)
#define FCVAR_DONTRECORD (1<<17) 
#define FCVAR_RELOAD_MATERIALS (1<<20)
#define FCVAR_RELOAD_TEXTURES (1<<21)
#define FCVAR_NOT_CONNECTED (1<<22)
#define FCVAR_MATERIAL_SYSTEM_THREAD (1<<23)
#define FCVAR_ARCHIVE_XBOX (1<<24)
#define FCVAR_ACCESSIBLE_FROM_THREADS (1<<25)
#define FCVAR_SERVER_CAN_EXECUTE (1<<28)
#define FCVAR_SERVER_CANNOT_QUERY (1<<29)
#define FCVAR_CLIENTCMD_CAN_EXECUTE (1<<30)
#define FCVAR_EXEC_DESPITE_DEFAULT (1<<31)
#define FCVAR_INTERNAL_USE (1<<15)
#define FCVAR_ALLOWED_IN_COMPETITIVE (1<<18)
#define FCVAR_MATERIAL_THREAD_MASK ( FCVAR_RELOAD_MATERIALS | FCVAR_RELOAD_TEXTURES | FCVAR_MATERIAL_SYSTEM_THREAD )	

typedef void (*FnChangeCallback_t)(IConVar* var, const char* pOldValue, float flOldValue);

class IConVar
{
public:
	virtual void SetValue(const char* pValue) = 0;
	virtual void SetValue(float flValue) = 0;
	virtual void SetValue(int nValue) = 0;
	virtual const char* GetName(void) const = 0;
	virtual bool IsFlagSet(int nFlag) const = 0;
};

class ConVar;
class CCommand;
class ConCommand;
class ConCommandBase;
struct characterset_t;

class IConCommandBaseAccessor
{
public:
	virtual bool RegisterConCommandBase(ConCommandBase* pVar) = 0;
};

typedef void (*FnCommandCallbackVoid_t)(void);
typedef void (*FnCommandCallback_t)(const CCommand& command);

#define COMMAND_COMPLETION_MAXITEMS 64
#define COMMAND_COMPLETION_ITEM_LENGTH 64

typedef int (*FnCommandCompletionCallback)(const char* partial, char commands[COMMAND_COMPLETION_MAXITEMS][COMMAND_COMPLETION_ITEM_LENGTH]);

class ICommandCallback
{
public:
	virtual void CommandCallback(const CCommand& command) = 0;
};

class ICommandCompletionCallback
{
public:
	virtual int CommandCompletionCallback(const char* pPartial, CUtlVector< /*CUtlString*/ void* >& commands) = 0;
};

class ConCommandBase
{
public:
	virtual ~ConCommandBase(void);
	virtual	bool IsCommand(void) const;
	virtual bool IsFlagSet(int flag) const;
	virtual void AddFlags(int flags);
	virtual const char* GetName(void) const;
	virtual const char* GetHelpText(void) const;
	virtual bool IsRegistered(void) const;
	virtual void* GetDLLIdentifier() const;
	virtual void CreateBase(const char* pName, const char* pHelpString = 0, int flags = 0);
	virtual void Init();

public:
	ConCommandBase* m_pNext;
	bool m_bRegistered;
	const char* m_pszName;
	const char* m_pszHelpString;
	int m_nFlags;

protected:
	static ConCommandBase* s_pConCommandBases;
	static IConCommandBaseAccessor* s_pAccessor;
};

enum
{
	COMMAND_MAX_ARGC = 64,
	COMMAND_MAX_LENGTH = 512
};

class CCommand
{
public:
	int m_nArgc;
	int m_nArgv0Size;
	char m_pArgSBuffer[COMMAND_MAX_LENGTH];
	char m_pArgvBuffer[COMMAND_MAX_LENGTH];
	const char* m_ppArgv[COMMAND_MAX_ARGC];
};

class ConCommand : public ConCommandBase
{
public:
	virtual ~ConCommand(void);
	virtual	bool IsCommand(void) const;
	virtual int AutoCompleteSuggest(const char* partial, CUtlVector< /*CUtlString*/ void* >& commands);
	virtual bool CanAutoComplete(void);
	virtual void Dispatch(const CCommand& command);

private:
	union
	{
		FnCommandCallbackVoid_t m_fnCommandCallbackV1;
		FnCommandCallback_t m_fnCommandCallback;
		ICommandCallback* m_pCommandCallback;
	};

	union
	{
		FnCommandCompletionCallback	m_fnCompletionCallback;
		ICommandCompletionCallback* m_pCommandCompletionCallback;
	};

	bool m_bHasCompletionCallback : 1;
	bool m_bUsingNewCommandCallback : 1;
	bool m_bUsingCommandCallbackInterface : 1;
};

class ConVar : public ConCommandBase, public IConVar
{
public:
	virtual ~ConVar(void);
	virtual bool IsFlagSet(int flag) const;
	virtual const char* GetHelpText(void) const;
	virtual bool IsRegistered(void) const;
	virtual const char* GetName(void) const;
	virtual void AddFlags(int flags);
	virtual	bool IsCommand(void) const;

	inline float GetFloat(void) const;
	inline int GetInt(void) const;
	inline bool GetBool() const { return !!GetInt(); }
	inline char const* GetString(void) const;

	virtual void SetValue(const char* value);
	virtual void SetValue(float value);
	virtual void SetValue(int value);

private:
	virtual void InternalSetValue(const char* value);
	virtual void InternalSetFloatValue(float fNewValue, bool bForce = false);
	virtual void InternalSetIntValue(int nValue);
	virtual bool ClampValue(float& value);
	virtual void ChangeStringValue(const char* tempVal, float flOldValue);
	virtual void Init();

	int GetFlags() { return m_pParent->m_nFlags; }

public:
	ConVar* m_pParent;
	const char* m_pszDefaultValue;
	char* m_pszString;
	int m_StringLength;
	float m_fValue;
	int m_nValue;
	bool m_bHasMin;
	float m_fMinVal;
	bool m_bHasMax;
	float m_fMaxVal;
	bool m_bHasCompMin;
	float m_fCompMinVal;
	bool m_bHasCompMax;
	float m_fCompMaxVal;
	bool m_bCompetitiveRestrictions;
	FnChangeCallback_t m_fnChangeCallback;
};

inline float ConVar::GetFloat(void) const
{
	return m_pParent->m_fValue;
}

inline int ConVar::GetInt(void) const
{
	return m_pParent->m_nValue;
}

inline const char* ConVar::GetString(void) const
{
	if (m_nFlags & FCVAR_NEVER_AS_STRING)
		return "FCVAR_NEVER_AS_STRING";

	return (m_pParent->m_pszString) ? m_pParent->m_pszString : "";
}

typedef int CVarDLLIdentifier_t;

class IConsoleDisplayFunc
{
public:
	virtual void ColorPrint(const Color& clr, const char* pMessage) = 0;
	virtual void Print(const char* pMessage) = 0;
	virtual void DPrint(const char* pMessage) = 0;
};

class ICvarQuery : public IAppSystem
{
public:
	virtual bool AreConVarsLinkable(const ConVar* child, const ConVar* parent) = 0;
};

class ICvar : public IAppSystem
{
public:
	virtual CVarDLLIdentifier_t AllocateDLLIdentifier() = 0;
	virtual void RegisterConCommand(ConCommandBase* pCommandBase) = 0;
	virtual void UnregisterConCommand(ConCommandBase* pCommandBase) = 0;
	virtual void UnregisterConCommands(CVarDLLIdentifier_t id) = 0;
	virtual const char* GetCommandLineValue(const char* pVariableName) = 0;
	virtual ConCommandBase* FindCommandBase(const char* name) = 0;
	virtual const ConCommandBase* FindCommandBase(const char* name) const = 0;
	virtual ConVar* FindVar(const char* var_name) = 0;
	virtual const ConVar* FindVar(const char* var_name) const = 0;
	virtual ConCommand* FindCommand(const char* name) = 0;
	virtual const ConCommand* FindCommand(const char* name) const = 0;
	virtual ConCommandBase* GetCommands(void) = 0;
	virtual const ConCommandBase* GetCommands(void) const = 0;
	virtual void InstallGlobalChangeCallback(FnChangeCallback_t callback) = 0;
	virtual void RemoveGlobalChangeCallback(FnChangeCallback_t callback) = 0;
	virtual void CallGlobalChangeCallbacks(ConVar* var, const char* pOldString, float flOldValue) = 0;
	virtual void InstallConsoleDisplayFunc(IConsoleDisplayFunc* pDisplayFunc) = 0;
	virtual void RemoveConsoleDisplayFunc(IConsoleDisplayFunc* pDisplayFunc) = 0;
	virtual void ConsoleColorPrintf(const Color& clr, const char* pFormat, ...) const = 0;
	virtual void ConsolePrintf(const char* pFormat, ...) const = 0;
	virtual void ConsoleDPrintf(const char* pFormat, ...) const = 0;
	virtual void RevertFlaggedConVars(int nFlag) = 0;
	virtual void InstallCVarQuery(ICvarQuery* pQuery) = 0;
	virtual bool IsMaterialThreadSetAllowed() const = 0;
	virtual void QueueMaterialThreadSetValue(ConVar* pConVar, const char* pValue) = 0;
	virtual void QueueMaterialThreadSetValue(ConVar* pConVar, int nValue) = 0;
	virtual void QueueMaterialThreadSetValue(ConVar* pConVar, float flValue) = 0;
	virtual bool HasQueuedMaterialThreadConVarSets() const = 0;
	virtual int ProcessQueuedMaterialThreadConVarSets() = 0;

	class ICVarIteratorInternal
	{
	public:
		virtual ~ICVarIteratorInternal() {}
		virtual void SetFirst(void) = 0;
		virtual void Next(void) = 0;
		virtual	bool IsValid(void) = 0;
		virtual ConCommandBase* Get(void) = 0;
	};

	class Iterator
	{
	public:
		inline Iterator(ICvar* icvar);
		inline ~Iterator(void);
		inline void SetFirst(void);
		inline void Next(void);
		inline bool IsValid(void);
		inline ConCommandBase* Get(void);
	private:
		ICVarIteratorInternal* m_pIter;
	};

	virtual ICVarIteratorInternal* FactoryInternalIterator(void) = 0;
};

inline ICvar::Iterator::Iterator(ICvar* icvar)
{
	m_pIter = icvar->FactoryInternalIterator();
}

inline ICvar::Iterator::~Iterator(void)
{
	//delete m_pIter;
}

inline void ICvar::Iterator::SetFirst(void)
{
	m_pIter->SetFirst();
}

inline void ICvar::Iterator::Next(void)
{
	m_pIter->Next();
}

inline bool ICvar::Iterator::IsValid(void)
{
	return m_pIter->IsValid();
}

inline ConCommandBase* ICvar::Iterator::Get(void)
{
	return m_pIter->Get();
}

namespace I { inline ICvar* Cvar = nullptr; }