// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

using namespace std;

// GLOBALS

bool PerforminActionReponse = false;

// Keymapping

char g_WATCHOUT = VK_NUMPAD0;
char g_SHIT = VK_NUMPAD1;
char g_GOAHEAD = VK_NUMPAD2;
char g_GOODWORK = VK_NUMPAD3;
char g_YOUTAKE = VK_NUMPAD4;
char g_CALLPARTNER = VK_NUMPAD5;
char g_FANOUT = VK_NUMPAD6;
char g_TAKECARE = VK_NUMPAD7;
char g_FOLLOWME = VK_NUMPAD8;
char g_IOWEYOU = VK_NUMPAD9;
char g_LEAVETOME = VK_DECIMAL;
char g_BECAREFUL = VK_NEXT;
char g_IMCOMING = VK_PRIOR;
char g_SAYYES = VK_ADD;
char g_SAYNO = VK_SUBTRACT;
char g_CALLPARTNERSOFT = VK_DIVIDE;
char g_CALLFORHELP = VK_MULTIPLY;
char g_CANTCARRY = VK_INSERT;
char g_NICESHOT = VK_DELETE;
char g_DYING = VK_HOME;
char g_PARTNERDEAD = VK_END;
char g_GO = VK_F1;
char g_WAIT = VK_F2;
char g_GIVEITEM = VK_F4;
char g_GIVEMEITEM = VK_F3;

// Custom Groups

unsigned short SHIT[3] = { 72, 73, 0 };
unsigned short BECAREFUL[4] = { 52, 53, 54, 0 };
unsigned short IMCOMING[3] = { 47, 48, 0 };
unsigned short CANTCARRY[4] = { 91, 92, 93, 0 };
unsigned short IOWEYOU[4] = { 49, 50, 51, 0 };
unsigned short FOLLOWME[3] = { 14, 15, 0 };
unsigned short TAKECARE[3] = { 96, 97, 0 };
unsigned short FANOUT[5] = { 17, 18, 25, 26, 0 };
unsigned short YOUTAKE[4] = { 94, 95, 0 };
unsigned short GOODWORK[4] = { 58, 59, 60, 0 };
unsigned short NICESHOT[4] = { 62, 63, 64, 0 };
unsigned short GOAHEAD[3] = { 98, 99, 0 };
unsigned short SAYYES[3] = { 19, 20, 0 };
unsigned short SAYNO[4] = { 22, 23, 24, 0 };
unsigned short CALLPARTNER[4] = { 41, 0, 42, 0 };
unsigned short CALLPARTNERSOFT[1] = { 0 };
unsigned short PARTNERDEAD[5] = { 0, 67, 68, 69, 1 };
unsigned short GIVEITEM[3] = { 32, 33, 0 };
unsigned short CALLFORHELP[3] = { 43, 44, 0 };
unsigned short DYING[3] = { 45, 46, 0 };
unsigned short LEAVETOME[1] = { 21 };
unsigned short GIVEMEITEM[1] = { 80 };
unsigned short GO[1] = { 16 };
unsigned short WAIT[1] = { 27 };

int KeyPressed(int VK)
{
	return GetAsyncKeyState(VK) & 0x8000;
}

DWORD WINAPI MainThread(LPVOID param)
{
	Sleep(4000);

	if (!Game::ValidateGameVersion())
	{
		MessageBox(0, "Unsupported game version, mod disabled.", "Resident Evil 5 - Vocalizer", MB_ICONINFORMATION);

		Sleep(100);
		FreeLibraryAndExitThread((HMODULE)param, 0);

		return 0;
	}

	while (true)
	{
		if (!Game::HasFocus() || Game::GetPlayerQuantity() == 0)
			continue;

		int LocalPlayerIndex = Game::GetLocalPlayerIndex();
		int LocalPlayer = Game::GetPlayerObjAddress(LocalPlayerIndex);

		if (LocalPlayer == 0 || *(int*)(LocalPlayer + 0x2674) != 0)
			continue;

		int Partner = *(int*)(LocalPlayer + 0x2A74);
		int PartnerIndex = Game::GetPlayerIndexByObjAddress(Partner);

		if (Partner != 0)
		{
			int LocalPlayerChar = Game::GetCharacter(LocalPlayerIndex);
			int PartnerChar = Game::GetCharacter(PartnerIndex);

			if (LocalPlayerChar != PartnerChar)
			{
				switch (PartnerChar)
				{
				case 0:
					CALLPARTNER[1] = 37;
					CALLPARTNERSOFT[0] = 10;
					PARTNERDEAD[0] = 67;
					break;
				case 1:
					CALLPARTNER[1] = 38;
					CALLPARTNERSOFT[0] = 11;
					PARTNERDEAD[0] = 68;
					break;
				case 2:
					CALLPARTNER[1] = 39;
					CALLPARTNERSOFT[0] = 12;
					PARTNERDEAD[0] = 69;
					break;
				case 3:
					CALLPARTNER[1] = 40;
					CALLPARTNERSOFT[0] = 13;
					PARTNERDEAD[0] = 70;
					break;
				case 4:
					CALLPARTNER[1] = 28;
					CALLPARTNERSOFT[0] = 6;
					PARTNERDEAD[0] = 55;
					break;
				case 5:
					CALLPARTNER[1] = 36;
					CALLPARTNERSOFT[0] = 9;
					PARTNERDEAD[0] = 65;
					break;
				case 6:
					CALLPARTNER[1] = 34;
					CALLPARTNERSOFT[0] = 7;
					PARTNERDEAD[0] = 56;
					break;
				case 7:
					CALLPARTNER[1] = 35;
					CALLPARTNERSOFT[0] = 8;
					PARTNERDEAD[0] = 57;
					break;
				default:
					CALLPARTNER[1] = 0;
					CALLPARTNERSOFT[0] = 0;
					PARTNERDEAD[0] = 0;
					break;
				}
			}
			else
			{
				CALLPARTNER[1] = 0;
				CALLPARTNERSOFT[0] = 0;
				PARTNERDEAD[0] = 0;
			}
		}
		else
		{
			CALLPARTNER[1] = 0;
			CALLPARTNERSOFT[0] = 0;
			PARTNERDEAD[0] = 0;
		}

		if (KeyPressed(g_WATCHOUT) != 0)
		{
			Game::PlaySpeech(79, LocalPlayer);
		}
		else if (KeyPressed(g_SHIT) != 0)
		{
			Game::PlaySpeech(SHIT[SHIT[2]], LocalPlayer);
			SHIT[2]++;
			SHIT[2] = SHIT[2] > 1 ? 0 : SHIT[2];
		}
		else if (KeyPressed(g_GOAHEAD) != 0)
		{
			Game::PlaySpeech(GOAHEAD[GOAHEAD[2]], LocalPlayer);
			GOAHEAD[2]++;
			GOAHEAD[2] = GOAHEAD[2] > 1 ? 0 : GOAHEAD[2];
		}
		else if (KeyPressed(g_GOODWORK) != 0)
		{
			Game::PlaySpeech(GOODWORK[GOODWORK[3]], LocalPlayer);
			GOODWORK[3]++;
			GOODWORK[3] = GOODWORK[3] > 2 ? 0 : GOODWORK[3];
		}
		else if (KeyPressed(g_YOUTAKE) != 0)
		{
			Game::PlaySpeech(YOUTAKE[YOUTAKE[3]], LocalPlayer);
			YOUTAKE[3]++;
			YOUTAKE[3] = YOUTAKE[3] > 2 ? 0 : YOUTAKE[3];
		}
		else if (KeyPressed(g_CALLPARTNER) != 0)
		{
			Game::PlaySpeech(CALLPARTNER[CALLPARTNER[3]], LocalPlayer);
			CALLPARTNER[3]++;
			CALLPARTNER[3] = CALLPARTNER[3] > 2 ? 0 : CALLPARTNER[3];
		}
		else if (KeyPressed(g_FANOUT) != 0)
		{
			Game::PlaySpeech(FANOUT[FANOUT[4]], LocalPlayer);
			FANOUT[4]++;
			FANOUT[4] = FANOUT[4] > 3 ? 0 : FANOUT[4];
		}
		else if (KeyPressed(g_TAKECARE) != 0)
		{
			Game::PlaySpeech(TAKECARE[TAKECARE[2]], LocalPlayer);
			TAKECARE[2]++;
			TAKECARE[2] = TAKECARE[2] > 1 ? 0 : TAKECARE[2];
		}
		else if (KeyPressed(g_FOLLOWME) != 0)
		{
			Game::PlaySpeech(FOLLOWME[FOLLOWME[2]], LocalPlayer);
			FOLLOWME[2]++;
			FOLLOWME[2] = FOLLOWME[2] > 1 ? 0 : FOLLOWME[2];
		}
		else if (KeyPressed(g_IOWEYOU) != 0)
		{
			Game::PlaySpeech(IOWEYOU[IOWEYOU[3]], LocalPlayer);
			IOWEYOU[3]++;
			IOWEYOU[3] = IOWEYOU[3] > 2 ? 0 : IOWEYOU[3];
		}
		else if (KeyPressed(g_SAYNO) != 0)
		{
			Game::PlaySpeech(SAYNO[SAYNO[3]], LocalPlayer);
			SAYNO[3]++;
			SAYNO[3] = SAYNO[3] > 2 ? 0 : SAYNO[3];
		}
		else if (KeyPressed(g_SAYYES) != 0)
		{
			Game::PlaySpeech(SAYYES[SAYYES[2]], LocalPlayer);
			SAYYES[2]++;
			SAYYES[2] = SAYYES[2] > 1 ? 0 : SAYYES[2];
		}
		else if (KeyPressed(g_LEAVETOME) != 0)
		{
			Game::PlaySpeech(LEAVETOME[0], LocalPlayer);
		}
		else if (KeyPressed(g_PARTNERDEAD) != 0)
		{
			int PlayerChar = Game::GetCharacter(LocalPlayerIndex);

			if (PlayerChar == 3) {
				Game::PlaySpeech(PARTNERDEAD[PARTNERDEAD[4]], LocalPlayer);
				PARTNERDEAD[4]++;
				PARTNERDEAD[4] = PARTNERDEAD[4] > 3 ? 1 : PARTNERDEAD[4];
			}
			else
				Game::PlaySpeech(PARTNERDEAD[0], LocalPlayer);
		}
		else if (KeyPressed(g_NICESHOT) != 0)
		{
			Game::PlaySpeech(NICESHOT[NICESHOT[3]], LocalPlayer);
			NICESHOT[3]++;
			NICESHOT[3] = NICESHOT[3] > 2 ? 0 : NICESHOT[3];
		}
		else if (KeyPressed(g_DYING) != 0)
		{
			Game::PlaySpeech(DYING[DYING[2]], LocalPlayer);
			DYING[2]++;
			DYING[2] = DYING[2] > 1 ? 0 : DYING[2];
		}
		else if (KeyPressed(g_CANTCARRY) != 0)
		{
			Game::PlaySpeech(CANTCARRY[CANTCARRY[3]], LocalPlayer);
			CANTCARRY[3]++;
			CANTCARRY[3] = CANTCARRY[3] > 2 ? 0 : CANTCARRY[3];
		}
		else if (KeyPressed(g_IMCOMING) != 0)
		{
			Game::PlaySpeech(IMCOMING[IMCOMING[2]], LocalPlayer);
			IMCOMING[2]++;
			IMCOMING[2] = IMCOMING[2] > 1 ? 0 : IMCOMING[2];
		}
		else if (KeyPressed(g_BECAREFUL) != 0)
		{
			Game::PlaySpeech(BECAREFUL[BECAREFUL[3]], LocalPlayer);
			BECAREFUL[3]++;
			BECAREFUL[3] = BECAREFUL[3] > 2 ? 0 : BECAREFUL[3];
		}
		else if (KeyPressed(g_CALLFORHELP) != 0)
		{
			Game::PlaySpeech(CALLFORHELP[CALLFORHELP[2]], LocalPlayer);
			CALLFORHELP[2]++;
			CALLFORHELP[2] = CALLFORHELP[2] > 1 ? 0 : CALLFORHELP[2];
		}
		else if (KeyPressed(g_CALLPARTNERSOFT) != 0)
		{
			Game::PlaySpeech(CALLPARTNERSOFT[0], LocalPlayer);
		}
		else if (KeyPressed(g_GO) != 0)
		{
			Game::PlaySpeech(GO[0], LocalPlayer);
		}
		else if (KeyPressed(g_WAIT) != 0)
		{
			Game::PlaySpeech(WAIT[0], LocalPlayer);
		}
		else if (KeyPressed(g_GIVEMEITEM) != 0)
		{
			if (Partner != 0)
			{
				for (int i = 0; i < 9; i++)
				{
					int Item = Game::GetRealTimeInventoryItem(Partner, i);
					bool Equipped = *(int*)(Item + 0x18) == 1;

					if (Equipped)
					{
						int ItemID = *(int*)(Item);

						switch (ItemID)
						{
						case 258: // Handgun
						case 272:
						case 273:
						case 286:
						case 287:
						case 297:
						case 274:
							GIVEMEITEM[0] = 82;
							break;
						case 260: // Shotgun
						case 278:
						case 279:
						case 281:
							GIVEMEITEM[0] = 83;
							break;
						case 261: // Rifle
						case 288:
						case 284:
							GIVEMEITEM[0] = 84;
							break;
						case 267: // Magnum
						case 282:
						case 283:
							GIVEMEITEM[0] = 85;
							break;
						case 259: // Machinegun
						case 285:
						case 275:
						case 265:
							GIVEMEITEM[0] = 86;
							break;
						case 269: // Rocket Launcher
						case 309:
							GIVEMEITEM[0] = 87;
							break;
						case 262: // Grenade
						case 263:
						case 264:
						case 266:
							GIVEMEITEM[0] = 31;
							break;
						case 268: // Other Weapon
						case 271:
						case 277:
						case 289:
						case 290:
						case 303:
						case 308:
						case 293:
						case 294:
						case 295:
						case 313:
						case 314:
						case 315:
							GIVEMEITEM[0] = 81;
							break;
						case 772: // First-Aid-Spray
							GIVEMEITEM[0] = 90;
							break;
						case 773: // Herb
						case 774:
						case 775:
						case 777:
							GIVEMEITEM[0] = 30;
							break;
						case 316: // Egg
						case 317:
						case 318:
							GIVEMEITEM[0] = 89;
							break;
						case 513: // Ammo
						case 514:
						case 515:
						case 516:
						case 521:
						case 518:
						case 519:
						case 520:
						case 526:
						case 527:
						case 528:
							GIVEMEITEM[0] = 29;
							break;
						default:
							GIVEMEITEM[0] = 88;
							break;
						}
					}
				}
			}
			else
				GIVEMEITEM[0] = 88;

			Game::PlaySpeech(GIVEMEITEM[0], LocalPlayer);
		}
		else if (KeyPressed(g_GIVEITEM) != 0)
		{
			Game::PlaySpeech(GIVEITEM[GIVEITEM[2]], LocalPlayer);
			GIVEITEM[2]++;
			GIVEITEM[2] = GIVEITEM[2] > 1 ? 0 : GIVEITEM[2];
		}

		// Action response

		int Move = *(int*)(LocalPlayer + 0x10E0);

		if (Move != 112 && Move != 100 && Move != 98 && Move != 31)
			PerforminActionReponse = false;
		else
		{
			if (!PerforminActionReponse)
			{
				PerforminActionReponse = true;

				switch (Move)
				{
				case 100:
					Game::PlaySpeech(GIVEITEM[GIVEITEM[2]], LocalPlayer);
					GIVEITEM[2]++;
					GIVEITEM[2] = GIVEITEM[2] > 1 ? 0 : GIVEITEM[2];
					break;
				case 112:
				case 98:
					Game::PlaySpeech(BECAREFUL[BECAREFUL[3]], LocalPlayer);
					BECAREFUL[3]++;
					BECAREFUL[3] = BECAREFUL[3] > 2 ? 0 : BECAREFUL[3];
					break;
				case 31:
				{
					for (int i = 0; i < 9; i++)
					{
						int Item = Game::GetRealTimeInventoryItem(LocalPlayer, i);
						bool Equipped = *(int*)(Item + 0x18) == 1;

						if (Equipped)
						{
							int Ammount = *(int*)(Item + 4);
							int MaxAmmount = *(int*)(Item + 8);

							if (Ammount < (MaxAmmount * 0.5))
								Game::PlaySpeech(66, LocalPlayer);
						}
					}

					break;
				}
				default:
					break;
				}
			}
		}
	}

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, MainThread, hModule, 0, 0);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

