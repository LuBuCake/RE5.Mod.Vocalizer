#pragma once

#include <Windows.h>

namespace Mod
{
	class Utils
	{
		public:

			static bool Hook(LPVOID ToHook, LPVOID Hook, LPVOID JumpBack, int Length);
	};
}