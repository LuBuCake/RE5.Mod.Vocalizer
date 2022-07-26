// INI Reader/Writer repo https://github.com/pulzed/mINI

#include "Vocalizer.h"
#include "Engine.h"
#include "Hooks.h"
#include "Utils.h"
#include "ini.h"
#include <string>
#include <psapi.h>
#include <tchar.h>

// TO DO:
// Anti-Spamming
// I need ammo action response

using namespace std;
using namespace Mod;

// Default Groups
unsigned short AGREE[3] = { 19, 20, 0 };
unsigned short DISAGREE[4] = { 22, 23, 24, 0 };
unsigned short ASSISTENCE[3] = { 96, 97, 0 };
unsigned short CALL[3] = { 41, 42, 0 };
unsigned short TAKECHARGE[4] = { 14, 15, 21, 0 };
unsigned short WARNING[1] = { 79 };
unsigned short FULLINVENTORY[4] = { 91, 92, 93, 0 };
unsigned short HELP[3] = { 43, 44, 0 };
unsigned short DYINGHELP[3] = { 45, 46, 0 };
unsigned short PRAISE[4] = { 49, 50, 51, 0 };
unsigned short PRAISEAIM[4] = { 62, 63, 64, 0 };
unsigned short PRAISETEAMWORK[4] = { 58, 59, 60, 0 };
unsigned short RESCUE[3] = { 47, 48, 0 };
unsigned short SPLITUP[5] = { 17, 18, 25, 26, 0 };
unsigned short SWEAR[3] = { 72, 73, 0 };
unsigned short PARTNERPICKUP[3] = { 94, 95, 0 };
unsigned short PARTNERTAKELEAD[3] = { 98, 99, 0 };
unsigned short PARTNERVIGILANCE[4] = { 52, 53, 54, 0 };
unsigned short PARTNERNAMESOFT[1] = { 0 };
unsigned short PARTNERNAMENORMAL[1] = { 0 };
unsigned short PARTNERNAMELOUD[5] = { 0, 67, 68, 69, 1 };

// Action Responses

bool ActionResponse = false;
bool PerformingActionResponse = false;

unsigned short RELOAD[1] = { 66 };
unsigned short GIVEITEM[3] = { 32, 33, 0 };
unsigned short NEEDAMMO[1] = { 29 };

bool Vocalizer::Validate()
{
	HMODULE EngineModules[1024];
	HANDLE EngineProcess;
	DWORD cbNeeded;

	EngineProcess = GetCurrentProcess();

	if (EnumProcessModules(EngineProcess, EngineModules, sizeof(EngineModules), &cbNeeded))
	{
		for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			TCHAR szModName[MAX_PATH];

			if (GetModuleFileNameEx(EngineProcess, EngineModules[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
			{
				if (_tcsstr(szModName, _T("QoL.dll")) || _tcsstr(szModName, _T("QOL.dll")) || _tcsstr(szModName, _T("qol.dll")))
					return true;
			}
		}
	}

	return false;
}

void Vocalizer::Initialize()
{
	Hooks::Initialize();

	mINI::INIFile Config(".\\Plugins\\Vocalizer.ini");
	mINI::INIStructure ini;
	bool FileExists = Config.read(ini);

	if (FileExists)
	{
		if (ini.get("VOCALIZER").get("ActionResponse").compare("ON") == 0)
		{
			ActionResponse = true;
		}
		else if (ini.get("VOCALIZER").get("ActionResponse").compare("OFF") != 0)
		{
			ActionResponse = true;

			ini["VOCALIZER"]["ActionResponse"] = "ON";
			Config.generate(ini);
		}
	}
	else
	{
		ActionResponse = true;

		ini["VOCALIZER"]["ActionResponse"] = "ON";
		Config.generate(ini, true);
	}

	while (true)
	{
		Update();
		UpdateAR();
	}
}

void Vocalizer::Update()
{
	if (Engine::GetPlayerQuantity() == 0 || Engine::GamePaused())
		return;

	int LocalPlayerIndex = Engine::GetLocalPlayerIndex();
	int LocalPlayer = Engine::GetPlayer(LocalPlayerIndex);

	if (LocalPlayer == 0 || *(int*)(LocalPlayer + 0x2674) != 0 || Engine::InventoryOpened(LocalPlayer))
		return;

	int Partner = *(int*)(LocalPlayer + 0x2A74);
	int PartnerIndex = Engine::GetPlayerIndex(Partner);

	if (Partner != 0)
	{
		int LocalPlayerCharacter = Engine::GetCharacter(LocalPlayerIndex);
		int PartnerCharacter = Engine::GetCharacter(PartnerIndex);

		if (LocalPlayerCharacter != PartnerCharacter)
		{
			switch (PartnerCharacter)
			{
				case 0:
					PARTNERNAMESOFT[0] = 10;
					PARTNERNAMENORMAL[0] = 37;
					PARTNERNAMELOUD[0] = 67;
					break;
				case 1:
					PARTNERNAMESOFT[0] = 11;
					PARTNERNAMENORMAL[0] = 38;
					PARTNERNAMELOUD[0] = 68;
					break;
				case 2:
					PARTNERNAMESOFT[0] = 12;
					PARTNERNAMENORMAL[0] = 39;
					PARTNERNAMELOUD[0] = 69;
					break;
				case 3:
					PARTNERNAMESOFT[0] = 13;
					PARTNERNAMENORMAL[0] = 40;
					PARTNERNAMELOUD[0] = 70;
					break;
				case 4:
					PARTNERNAMESOFT[0] = 6;
					PARTNERNAMENORMAL[0] = 28;
					PARTNERNAMELOUD[0] = 55;
					break;
				case 5:
					PARTNERNAMESOFT[0] = 9;
					PARTNERNAMENORMAL[0] = 36;
					PARTNERNAMELOUD[0] = 65;
					break;
				case 6:
					PARTNERNAMESOFT[0] = 7;
					PARTNERNAMENORMAL[0] = 34;
					PARTNERNAMELOUD[0] = 56;
					break;
				case 7:
					PARTNERNAMESOFT[0] = 8;
					PARTNERNAMENORMAL[0] = 35;
					PARTNERNAMELOUD[0] = 57;
					break;
				default:
					PARTNERNAMESOFT[0] = 0;
					PARTNERNAMENORMAL[0] = 0;
					PARTNERNAMELOUD[0] = 0;
					break;
			}
		}
		else
		{
			PARTNERNAMESOFT[0] = 0;
			PARTNERNAMENORMAL[0] = 0;
			PARTNERNAMELOUD[0] = 0;
		}
	}
	else
	{
		PARTNERNAMESOFT[0] = 0;
		PARTNERNAMENORMAL[0] = 0;
		PARTNERNAMELOUD[0] = 0;
	}

	if ((char)Engine::KeyPressed(Bind::AGREE) != '\0')
	{
		Engine::PlaySpeech(AGREE[AGREE[2]], LocalPlayer);
		AGREE[2]++; 
		AGREE[2] = AGREE[2] > 1 ? 0 : AGREE[2];
	}
	else if ((char)Engine::KeyPressed(Bind::DISAGREE) != '\0')
	{
		Engine::PlaySpeech(DISAGREE[DISAGREE[3]], LocalPlayer);
		DISAGREE[3]++;
		DISAGREE[3] = DISAGREE[3] > 2 ? 0 : DISAGREE[3];
	}
	else if ((char)Engine::KeyPressed(Bind::ASSISTENCE) != '\0')
	{
		Engine::PlaySpeech(ASSISTENCE[ASSISTENCE[2]], LocalPlayer);
		ASSISTENCE[2]++;
		ASSISTENCE[2] = ASSISTENCE[2] > 1 ? 0 : ASSISTENCE[2];
	}
	else if ((char)Engine::KeyPressed(Bind::CALL) != '\0')
	{
		Engine::PlaySpeech(CALL[CALL[2]], LocalPlayer);
		CALL[2]++;
		CALL[2] = CALL[2] > 1 ? 0 : CALL[2];
	}
	else if ((char)Engine::KeyPressed(Bind::TAKECHARGE) != '\0')
	{
		Engine::PlaySpeech(TAKECHARGE[TAKECHARGE[3]], LocalPlayer);
		TAKECHARGE[3]++;
		TAKECHARGE[3] = TAKECHARGE[3] > 2 ? 0 : TAKECHARGE[3];
	}
	else if ((char)Engine::KeyPressed(Bind::WARNING) != '\0')
	{
		Engine::PlaySpeech(WARNING[0], LocalPlayer);
	}
	else if ((char)Engine::KeyPressed(Bind::FULLINVENTORY) != '\0')
	{
		Engine::PlaySpeech(FULLINVENTORY[FULLINVENTORY[3]], LocalPlayer);
		FULLINVENTORY[3]++;
		FULLINVENTORY[3] = FULLINVENTORY[3] > 2 ? 0 : FULLINVENTORY[3];
	}
	else if ((char)Engine::KeyPressed(Bind::HELP) != '\0')
	{
		Engine::PlaySpeech(HELP[HELP[2]], LocalPlayer);
		HELP[2]++;
		HELP[2] = HELP[2] > 1 ? 0 : HELP[2];
	}
	else if ((char)Engine::KeyPressed(Bind::DYINGHELP) != '\0')
	{
		Engine::PlaySpeech(DYINGHELP[DYINGHELP[2]], LocalPlayer);
		DYINGHELP[2]++;
		DYINGHELP[2] = DYINGHELP[2] > 1 ? 0 : DYINGHELP[2];
	}
	else if ((char)Engine::KeyPressed(Bind::PRAISE) != '\0')
	{
		Engine::PlaySpeech(PRAISE[PRAISE[3]], LocalPlayer);
		PRAISE[3]++;
		PRAISE[3] = PRAISE[3] > 2 ? 0 : PRAISE[3];
	}
	else if ((char)Engine::KeyPressed(Bind::PRAISEAIM) != '\0')
	{
		Engine::PlaySpeech(PRAISEAIM[PRAISEAIM[3]], LocalPlayer);
		PRAISEAIM[3]++;
		PRAISEAIM[3] = PRAISEAIM[3] > 2 ? 0 : PRAISEAIM[3];
	}
	else if ((char)Engine::KeyPressed(Bind::PRAISETEAMWORK) != '\0')
	{
		Engine::PlaySpeech(PRAISETEAMWORK[PRAISETEAMWORK[3]], LocalPlayer);
		PRAISETEAMWORK[3]++;
		PRAISETEAMWORK[3] = PRAISETEAMWORK[3] > 2 ? 0 : PRAISETEAMWORK[3];
	}
	else if ((char)Engine::KeyPressed(Bind::RESCUE) != '\0')
	{
		Engine::PlaySpeech(RESCUE[RESCUE[2]], LocalPlayer);
		RESCUE[2]++;
		RESCUE[2] = RESCUE[2] > 1 ? 0 : RESCUE[2];
	}
	else if ((char)Engine::KeyPressed(Bind::SPLITUP) != '\0')
	{
		Engine::PlaySpeech(SPLITUP[SPLITUP[4]], LocalPlayer);
		SPLITUP[4]++;
		SPLITUP[4] = SPLITUP[4] > 3 ? 0 : SPLITUP[4];
	}
	else if ((char)Engine::KeyPressed(Bind::SWEAR) != '\0')
	{
		Engine::PlaySpeech(SWEAR[SWEAR[2]], LocalPlayer);
		SWEAR[2]++;
		SWEAR[2] = SWEAR[2] > 1 ? 0 : SWEAR[2];
	}
	else if ((char)Engine::KeyPressed(Bind::PARTNERPICKUP) != '\0')
	{
		Engine::PlaySpeech(PARTNERPICKUP[PARTNERPICKUP[2]], LocalPlayer);
		PARTNERPICKUP[2]++;
		PARTNERPICKUP[2] = PARTNERPICKUP[2] > 1 ? 0 : PARTNERPICKUP[2];
	}
	else if ((char)Engine::KeyPressed(Bind::PARTNERTAKELEAD) != '\0')
	{
		Engine::PlaySpeech(PARTNERTAKELEAD[PARTNERTAKELEAD[2]], LocalPlayer);
		PARTNERTAKELEAD[2]++;
		PARTNERTAKELEAD[2] = PARTNERTAKELEAD[2] > 1 ? 0 : PARTNERTAKELEAD[2];
	}
	else if ((char)Engine::KeyPressed(Bind::PARTNERVIGILANCE) != '\0')
	{
		Engine::PlaySpeech(PARTNERVIGILANCE[PARTNERVIGILANCE[3]], LocalPlayer);
		PARTNERVIGILANCE[3]++;
		PARTNERVIGILANCE[3] = PARTNERVIGILANCE[3] > 2 ? 0 : PARTNERVIGILANCE[3];
	}
	else if ((char)Engine::KeyPressed(Bind::PARTNERNAMESOFT) != '\0')
	{
		Engine::PlaySpeech(PARTNERNAMESOFT[0], LocalPlayer);
	}
	else if ((char)Engine::KeyPressed(Bind::PARTNERNAMENORMAL) != '\0')
	{
		Engine::PlaySpeech(PARTNERNAMENORMAL[0], LocalPlayer);
	}
	else if ((char)Engine::KeyPressed(Bind::PARTNERNAMELOUD) != '\0')
	{
		int LocalPlayerCharacter = Engine::GetCharacter(LocalPlayerIndex);

		if (LocalPlayerCharacter == 3) {
			Engine::PlaySpeech(PARTNERNAMELOUD[PARTNERNAMELOUD[4]], LocalPlayer);
			PARTNERNAMELOUD[4]++;
			PARTNERNAMELOUD[4] = PARTNERNAMELOUD[4] > 3 ? 1 : PARTNERNAMELOUD[4];
		}
		else
			Engine::PlaySpeech(PARTNERNAMELOUD[0], LocalPlayer);
	}
}

void Vocalizer::UpdateAR()
{
	if (!ActionResponse)
		return;

	if (Engine::GetPlayerQuantity() == 0 || Engine::GamePaused())
		return;

	int LocalPlayerIndex = Engine::GetLocalPlayerIndex();
	int LocalPlayer = Engine::GetPlayer(LocalPlayerIndex);

	if (LocalPlayer == 0 || *(int*)(LocalPlayer + 0x2674) != 0)
		return;

	int Move = *(int*)(LocalPlayer + 0x10E0);

	if (Move != 112 && Move != 100 && Move != 98 && Move != 31 && Move != 30)
		PerformingActionResponse = false;
	else
	{
		if (!PerformingActionResponse)
		{
			switch (Move)
			{
			case 100:
				PerformingActionResponse = true;
				Engine::PlaySpeech(GIVEITEM[GIVEITEM[2]], LocalPlayer);
				GIVEITEM[2]++;
				GIVEITEM[2] = GIVEITEM[2] > 1 ? 0 : GIVEITEM[2];
				break;
			case 112:
			case 98:
				PerformingActionResponse = true;
				Engine::PlaySpeech(PARTNERVIGILANCE[PARTNERVIGILANCE[3]], LocalPlayer);
				PARTNERVIGILANCE[3]++;
				PARTNERVIGILANCE[3] = PARTNERVIGILANCE[3] > 2 ? 0 : PARTNERVIGILANCE[3];
				break;
			case 31:
			{
				PerformingActionResponse = true;

				for (int i = 0; i < 9; i++)
				{
					int Item = Engine::GetRealTimeInventoryItem(LocalPlayer, i);
					bool Equipped = *(int*)(Item + 0x18) == 1;

					if (Equipped)
					{
						int Ammount = *(int*)(Item + 4);
						int MaxAmmount = *(int*)(Item + 8);

						if (Ammount < (MaxAmmount * 0.5))
							Engine::PlaySpeech(RELOAD[0], LocalPlayer);
					}
				}

				break;
			}
			case 30:
			{
				Sleep(10);

				ItemType EquippedItemType = Engine::GetEquippedItemType(LocalPlayer);
				int EquippedItem = Engine::GetEquippedItem(LocalPlayer);
				int AmmoID = -1;

				switch (EquippedItemType)
				{
				case ItemType::HANDGUN:
					AmmoID = 513;
					break;
				case ItemType::MACHINEGUN:
					AmmoID = 514;
					break;
				case ItemType::SHOTGUN:
					AmmoID = 515;
					break;
				case ItemType::RIFLE:
					AmmoID = 516;
					break;
				case ItemType::MAGNUM:
					AmmoID = 521;
					break;
				default:
					break;
				}

				if (AmmoID < 0 || EquippedItem == 0)
					break;

				int Clip = *(int*)(EquippedItem + 4);
				int AvailableAmmo = Engine::GetItemQuantity(LocalPlayer, AmmoID);

				if (Clip == 0 && AvailableAmmo == 0)
				{
					PerformingActionResponse = true;
					Engine::PlaySpeech(NEEDAMMO[0], LocalPlayer);
				}

				break;
			}
			default:
				break;
			}
		}
	}
}