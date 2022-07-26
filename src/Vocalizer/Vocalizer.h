#pragma once

#include <Windows.h>

namespace Mod
{
	class Vocalizer
	{
		public:

			static bool Validate();

			static void Initialize();
			static void Update();
			static void UpdateAR();
	};
}