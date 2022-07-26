#include "Engine.h"
#include "Hooks.h"

using namespace Mod;

int Engine::GetGameObject()
{
	n_GamePtr* F = (n_GamePtr*)reinterpret_cast<void*>(0x43B5B0);
	return F();
}

int Engine::GetGameLanguage()
{
	n_GetGameLanguage* F = (n_GetGameLanguage*)reinterpret_cast<void*>(0x719A20);
	return F();
}

unsigned int Engine::KeyPressed(Bind Key)
{
	n_KeyPress F = (n_KeyPress)(0x79E8C0);
	return F((LPVOID)((int)Key));
}

bool Engine::InventoryOpened(int Player)
{
	int param = *(int*)(Player + 0x2654);

	if (param == 0)
		return false;

	if ((*(char*)(param + 0x68) != '\0') && (0.0 < *(float*)(param + 0x50)))
		return true;

	return false;
}

bool Engine::GamePaused()
{
	unsigned int CurrentHUDState = *(unsigned int*)(*(int*)(0x123986C) + 0x10438);

	/*
	if (CurrentHUDState == (int)HUDState::PAUSEMENU || CurrentHUDState == (int)HUDState::PAUSEMENUEX || CurrentHUDState == (int)HUDState::ONLINEPAUSEMENU)
		return true;
	*/

	if ((CurrentHUDState & 0x1000) != 0)
		return true;

	return false;
}

void Engine::PlaySpeech(unsigned short Speech, int Player)
{
	if (Speech == 0)
		return;

	n_LocalSpeech F_A = (n_LocalSpeech)(0xB7A090);
	n_BroadcastSpeech F_B = (n_BroadcastSpeech)(0x7972D0);

	int DAT = *(int*)(0x123AD50);

	F_A((PVOID)Player, Speech, 0, 1);
	F_B((PVOID)DAT, Player, Speech, 0, 1);
}

int Engine::GetItemQuantity(int Player, int ItemID)
{
	int InventoryStart = Player + 0x21A0;
	
	n_GetItemQuantity F = (n_GetItemQuantity)(0xC4AE00);
	return F((PVOID)InventoryStart, ItemID);
}

int Engine::GetLocalPlayerIndex()
{
	int GameObj = GetGameObject();
	int Index = 0;
	unsigned int AND = 1;

	do
	{
		if ((AND & *(unsigned int*)(*(int*)(GameObj + 0x1042C) + 0x47C)) != 0)
			return Index;

		Index += 1;
		AND *= 2;
	} while (Index < 4);

	return Index;
}

int Engine::GetPlayerQuantity()
{
	return *(int*)(*(int*)(GetGameObject() + 0x103C8) + 0x34);
}

int Engine::GetPlayer(int Index)
{
	return *(int*)(*(int*)(GetGameObject() + 0x103C8) + 0x24 + (Index * 4));
}

int Engine::GetPlayerIndex(int Player)
{
	if (Player == 0)
		return 0;

	for (int index = 0; index < 4; index++)
	{
		int PlayerObj = GetPlayer(index);

		if (PlayerObj == Player)
			return index;
	}

	return 0;
}

int Engine::GetCharacter(int Index)
{
	return *(int*)(*(int*)(GetGameObject() + 0x103C8) + 0x6FE08 + (Index * 0x50));
}

int Engine::GetRealTimeInventoryItem(int Player, int Slot)
{
	return Player + 0x21A8 + (Slot * 0x30);
}

int Engine::GetEquippedItem(int Player)
{
	for (int i = 0; i < 9; i++)
	{
		int Item = Engine::GetRealTimeInventoryItem(Player, i);
		bool Equipped = *(int*)(Item + 0x18) == 1;

		if (Equipped)
			return Item;
	}

	return 0;
}

ItemType Engine::GetEquippedItemType(int Player)
{
	int Item = Engine::GetEquippedItem(Player);

	if (Item == 0)
		return ItemType::NONE;

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
		{
			return ItemType::HANDGUN;
		}
		case 260: // Shotgun
		case 278:
		case 279:
		case 281:
		{
			return ItemType::SHOTGUN;
		}
		case 261: // Rifle
		case 288:
		case 284:
		{
			return ItemType::RIFLE;
		}
		case 267: // Magnum
		case 282:
		case 283:
		{
			return ItemType::MAGNUM;
		}
		case 259: // Machinegun
		case 285:
		case 275:
		case 265:
		{
			return ItemType::MACHINEGUN;
		}
		case 269: // Rocket Launcher
		case 309:
		{
			return ItemType::ROCKETLAUNCHER;
		}
		case 293:
		case 294:
		case 295:
		case 313:
		case 314:
		case 315:
		{
			return ItemType::GRENADELAUNCHER;
		}
		case 262: // Grenade
		case 263:
		case 264:
		case 266:
		{
			return ItemType::GRENADE;
		}
		case 277:// Gun				
		case 303:
		{
			return ItemType::GUN;
		}
		case 271: // Weapon
		case 268:
		case 289:
		case 290:
		case 308:
		{
			return ItemType::WEAPON;
		}
		default:
			return ItemType::NONE;
	}
}