#pragma once

using namespace std;

class Game
{
public:
    static bool HasFocus();
    static bool ValidateGameVersion();
    static int GetGameObjAddress();
    static int GetPlayerObjAddress(int Index);
    static void PlaySpeech(unsigned short Speech, int Player);
    static int GetPlayerQuantity();
    static int GetLocalPlayerIndex();
    static int GetPlayerIndexByObjAddress(int ObjAddress);
    static int GetCharacter(int Index);
    static int GetRealTimeInventoryItem(int Player, int Slot);
};