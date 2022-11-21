#define WIN32_LEAN_AND_MEAN

#include "DefaultTypes.h"
#include "Hooks.h"
#include "Helpers.h"

HANDLE hThread;
HMODULE moduleInstance;
DWORD threadId;


undefined4 FUN_0047ac10(void* _this, uint param_1, Point* param_2) {
    undefined4 (* func)(void*, uint, Point *) = (undefined4(*)(void*, uint, Point*))0x0047ac10;
 
    return func(_this, param_1, param_2);
}

void ThreadWorker(LPVOID par) {
    OutputDebugStringA("\nEnter to worker\n");

    try
    {
        GUI::Setup();
        Hooks::Setup();
    }
    catch (const std::exception& err)
    {
        MessageBoxA(0, 
            err.what(), 
            "MultiplayerDLL", 
            MB_OK | MB_ICONEXCLAMATION);

        goto UNLOAD;
    }

    while (!GetAsyncKeyState(VK_END))
        Sleep(200);

UNLOAD:
    Hooks::Destroy();
    GUI::Destroy();

    FreeLibraryAndExitThread(*(HMODULE*)par, 0);

    OutputDebugStringA("\nExit from worker\n");
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    auto str = StringFormat("Incoming message: %d\n", ul_reason_for_call);
    OutputDebugStringA(str.c_str());

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        MessageBox(NULL, L"Attached multiplayer.dll", L"Multiplayer", 0);

        moduleInstance = hModule;
        
        DisableThreadLibraryCalls(hModule);

        hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadWorker, hModule, NULL, &threadId);

        if (hThread)
            CloseHandle(hThread);

        OutputDebugString(L"Test");
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        OutputDebugString(L"Exit from multiplayer.dll");
        break;
    }
    return TRUE;
}

