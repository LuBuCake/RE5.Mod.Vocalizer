#pragma once

#include <Windows.h>

namespace Mod
{
	enum class Bind
	{
		AGREE = 0x28,
		DISAGREE = 0x29,
		ASSISTENCE = 0x2A,
		CALL = 0x2B,
		TAKECHARGE = 0x2C,
		WARNING = 0x2D,
		FULLINVENTORY = 0x2E,
		HELP = 0x2F,
		DYINGHELP = 0x30,
		PRAISE = 0x31,
		PRAISEAIM = 0x32,
		PRAISETEAMWORK = 0x33,
		RESCUE = 0x34,
		SPLITUP = 0x35,
		SWEAR = 0x36,
		PARTNERPICKUP = 0x37,
		PARTNERTAKELEAD = 0x38,
		PARTNERVIGILANCE = 0x39,
		PARTNERNAMESOFT = 0x3A,
		PARTNERNAMENORMAL = 0x3B,
		PARTNERNAMELOUD = 0x3C
	};

	enum class HUDState
	{
		PAUSEMENU = 6144,
		PAUSEMENUEX = 6148,
		ONLINEPAUSEMENU = 4096
	};

	enum class ItemType
	{
		NONE,
		GUN,
		WEAPON,
		HANDGUN,
		SHOTGUN,
		RIFLE,
		MAGNUM,
		MACHINEGUN,
		ROCKETLAUNCHER,
		GRENADELAUNCHER,
		FIRSTAIDSPRAY,
		HERB,
		GRENADE,
		AMMO
	};

	enum class ItemIDs
	{
		M92F = 258,
		HKP8 = 272,
		SIGP226 = 273,
		M93R = 286,
		SAMURAIEDGE = 297,
		SAMURAIEDGEBARRY = 274,
		PX4 = 287,
		ITHACA = 260,
		M3 = 278,
		JAILBREAKER = 279,
		HYDRA = 281,
		VZ61 = 259,
		AK74 = 285,
		MP5 = 275,
		SIG556 = 265,
		S75 = 261,
		DRAGUNOV = 288,
		PSG1 = 284,
		SWM29 = 267,
		LHAWK = 282,
		SWM500 = 283,
		GLICE = 295,
		GLFLASH = 314,
		GLACID = 294,
		GLELETRIC = 315,
		GLEXPLOSIVE = 293,
		GLFLAME = 313,
		ROCKETLAUNCHER = 269,
		STUNROD = 290,
		GLATLINGGUN = 277,
		LONGBOW = 271,
		FIRSTAIDSPRAY = 772,
		GRENADEEXPLOSIVE = 262,
		GRENADEFLAME = 263,
		GRENADEFLASH = 264,
		FLASHROUNDS = 527,
		ACIDROUNDS = 519,
		ELETRICROUNDS = 528,
		ICEROUNDS = 520,
		FRAMEROUNDS = 526,
		EXPLOSIVEROUNDS = 518,
		HERBG = 773,
		HERBR = 774,
		HERBGG = 775,
		HERBGR = 777,
		AMMOHG = 513,
		AMMOSMG = 514,
		AMMOSTG = 515,
		AMMORFL = 516,
		AMMOMGN = 521
	};

	typedef int(__thiscall* n_GetItemQuantity)(PVOID, int);
	typedef void(__thiscall* n_LocalSpeech)(PVOID, unsigned short, short, unsigned short);
	typedef void(__thiscall* n_BroadcastSpeech)(PVOID, int, unsigned short, unsigned short, unsigned short);
	typedef unsigned int(__stdcall* n_KeyPress)(LPVOID);
	typedef int n_GamePtr(void);
	typedef int n_GetGameLanguage(void);

	class Engine
	{
		public:

			static int GetGameObject();
			static int GetGameLanguage();
			static unsigned int KeyPressed(Bind Key);
			static bool InventoryOpened(int Player);
			static bool GamePaused();
			static void PlaySpeech(unsigned short Speech, int Player);
			static int GetItemQuantity(int Player, int ItemID);

			static int GetLocalPlayerIndex();
			static int GetPlayerQuantity();
			static int GetPlayer(int Index);
			static int GetPlayerIndex(int Player);
			static int GetCharacter(int Index);
			static int GetRealTimeInventoryItem(int Player, int Slot);
			static int GetEquippedItem(int Player);
			static ItemType GetEquippedItemType(int Player);
	};
}