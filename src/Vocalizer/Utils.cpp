#include "Utils.h"

using namespace Mod;

bool Utils::Hook(LPVOID ToHook, LPVOID Hook, LPVOID JumpBack, int Length)
{
	DWORD P;
	BOOL PB = VirtualProtect(ToHook, Length, PAGE_EXECUTE_READWRITE, &P);

	if (!PB) return PB;

	memset(ToHook, 0x90, Length);

	*(BYTE*)ToHook = 0xE9;
	*(DWORD*)((DWORD)ToHook + 1) = ((DWORD)Hook - (DWORD)ToHook) - 5;

	if (JumpBack != NULL)
		*(DWORD*)JumpBack = (DWORD)ToHook + Length;

	DWORD C;
	BOOL CB = VirtualProtect(ToHook, Length, P, &C);

	if (!CB) return CB;

	return true;
}