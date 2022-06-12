#pragma once

#include "const.h"

#define DWordSwap DWordSwapAsm
#define LittleLong( val ) DWordSwap( val )

typedef int qboolean;
typedef unsigned long ULONG;
typedef unsigned char BYTE;
typedef unsigned char byte;
typedef unsigned short word;
typedef wchar_t ucs2;

enum ThreeState_t
{
	TRS_FALSE,
	TRS_TRUE,
	TRS_NONE
};

typedef float vec_t;

struct color24
{
	byte r, g, b;
};

typedef struct color32_s
{
	byte r, g, b, a;
} color32;

struct colorVec
{
	unsigned r, g, b, a;
};

struct vrect_t
{
	int x, y, width, height;
	vrect_t* pnext;
};

struct Rect_t
{
	int x, y;
	int width, height;
};

struct interval_t
{
	float start;
	float range;
};

using uint32 = unsigned int;
typedef unsigned char uint8;
typedef signed char int8;
typedef __int16 int16;
typedef unsigned __int16 uint16;
typedef __int32 int32;
typedef unsigned __int32 uint32;
typedef __int64 int64;
typedef unsigned __int64 uint64;
typedef __int32 intp;
typedef unsigned __int32 uintp;
typedef uint32 RTime32;
typedef float float32;
typedef double float64;
typedef unsigned int uint;

using DWORD = unsigned long;

template <typename T>
inline T DWordSwapAsm(T dw)
{
	__asm
	{
		mov eax, dw
		bswap eax
	}
}