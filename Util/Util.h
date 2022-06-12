#pragma once

#include "Hash/Hash.h"

#include <algorithm>
#include <string>
#include <vector>
#include <map>

namespace Util
{
	static std::wstring ConvertUtf8ToWide(const std::string& str)
	{
		int cnt = MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), NULL, 0);

		std::wstring s(cnt, 0);
		MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), &s[0], cnt);

		return s;
	}
}

#define FAILED_TO_HOOK false

#define CREATE_HOOK(name, address, type, callconvo, ...) namespace Hooks \
{ \
	namespace name \
	{ \
		inline Hook::C_Function Func; \
		using FN = type(callconvo*)(__VA_ARGS__); \
		type callconvo Detour(__VA_ARGS__); \
		inline void Initialize() \
		{ \
			XASSERT(Func.Initialize(reinterpret_cast<void*>(address), &Detour) == FAILED_TO_HOOK); \
		} \
	}\
}

#define DEFINE_HOOK(name, type, callconvo, ...) type callconvo Hooks::name::Detour(__VA_ARGS__)