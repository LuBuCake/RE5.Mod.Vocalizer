#include "pch.h"

using namespace std;

//-----------------------------------GAME VALIDATION-----------------------------------//

bool Game::HasFocus()
{
    HWND FocusedApp = GetForegroundWindow();

    DWORD PID;
    DWORD IDA = GetWindowThreadProcessId(FocusedApp, &PID);

    if (PID != 0)
    {
        HANDLE pHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, PID);

        if (pHandle)
        {
            TCHAR Buffer[MAX_PATH];

            if (GetModuleFileNameEx(pHandle, 0, Buffer, MAX_PATH))
            {
                if (_tcsstr(Buffer, _T("re5dx9.exe")))
                {
                    CloseHandle(pHandle);
                    return true;
                }
            }

            CloseHandle(pHandle);
        }
    }

    return false;
}

bool Game::ValidateGameVersion()
{
    HMODULE GameModules[1024];
    HANDLE GameProcess;
    DWORD cbNeeded;

    GameProcess = GetCurrentProcess();

    if (EnumProcessModules(GameProcess, GameModules, sizeof(GameModules), &cbNeeded))
    {
        for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
        {
            TCHAR szModName[MAX_PATH];

            if (GetModuleFileNameEx(GameProcess, GameModules[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
            {
                if (_tcsstr(szModName, _T("maluc.dll")))
                    return true;
            }
        }
    }

    return false;
}

//-----------------------------------GAME FUNCTIONS-----------------------------------//

void Game::PlaySpeech(unsigned short Speech, int Player)
{
    if (Speech == 0)
        return;

    typedef void(__thiscall* fSpeechA)(PVOID, unsigned short, short, unsigned short);
    typedef void(__thiscall* fSpeechB)(PVOID, int, unsigned short, unsigned short, unsigned short);

    fSpeechA F_A = (fSpeechA)(0xB7A090);
    fSpeechB F_B = (fSpeechB)(0x7972D0);

    int DAT = *(int*)(0x123AD50);

    F_A((PVOID)Player, Speech, 0, 1);
    F_B((PVOID)DAT, Player, Speech, 0, 1);
}

//-----------------------------------GAME OBJECTS-----------------------------------//

int Game::GetGameObjAddress()
{
    typedef int GameObj(void);
    GameObj* Func = (GameObj*)reinterpret_cast<void*>(0x43B5B0);
    return Func();
}

int Game::GetPlayerObjAddress(int Index)
{
    return *(int*)(*(int*)(GetGameObjAddress() + 0x103C8) + 0x24 + (Index * 4));
}

//-----------------------------------HELPERS-----------------------------------//

int Game::GetPlayerQuantity()
{
    return *(int*)(*(int*)(GetGameObjAddress() + 0x103C8) + 0x34);
}

int Game::GetLocalPlayerIndex()
{
    int GameObj = GetGameObjAddress();
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

int Game::GetPlayerIndexByObjAddress(int ObjAddress)
{
    if (ObjAddress == 0)
        return 0;

    for (int index = 0; index < 4; index++)
    {
        int PlayerObj = GetPlayerObjAddress(index);

        if (PlayerObj == ObjAddress)
            return index;
    }

    return 0;
}

int Game::GetCharacter(int Index)
{
    return *(int*)(*(int*)(GetGameObjAddress() + 0x103C8) + 0x6FE08 + (Index * 0x50));
}

int Game::GetRealTimeInventoryItem(int Player, int Slot)
{
    return Player + 0x21A8 + (Slot * 0x30);
}