//#include "MinHook.h"
//#pragma comment(lib, "libMinHook.x86.lib")

#include <windows.h>
#include "Engine.h"
#include "Vocalizer.h"

using namespace Mod;

DWORD WINAPI MainThread(LPVOID param)
{
    Sleep(1000);

    if (!Vocalizer::Validate())
    {
        MessageBox(0, L"Quality of Life Fixes missing, please refer to the documentation in order to install all prequisites.", L"RESIDENT EVIL 5: Vocalizer.dll - Mod Disabled", MB_ICONINFORMATION);
        
        FreeLibraryAndExitThread((HMODULE)param, 0);
        return 0;
    }

    Vocalizer::Initialize();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            CreateThread(0, 0, MainThread, hModule, 0, 0);
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}

