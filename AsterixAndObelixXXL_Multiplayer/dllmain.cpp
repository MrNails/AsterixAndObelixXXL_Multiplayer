#define WIN32_LEAN_AND_MEAN

#include "DefaultTypes.h"
#include "Hooks.h"
#include "Helpers.h"

HANDLE hThread;
HMODULE moduleInstance;
DWORD threadId;

undefined4 FUN_0047ac10(void* _this, uint param_1, Point* param_2) {
    auto func = (undefined4(__thiscall*)(void*, uint, Point*))0x0047ac10;

    return func(_this, param_1, param_2);
}

void Button_Clicked(const GUI::Button* btn) {

}

void SetupGUI() {
    auto mainWnd = new GUI::Window("Multiplayer GUI by MrNails");
    auto mainWndControls = mainWnd->GetControls();
    auto btn = new GUI::Button();

    btn->SetOnClichHandler(Button_Clicked);

    mainWndControls->push_back(new GUI::TextBlock("Test"));
    mainWndControls->push_back(new GUI::TextBlock("Test2"));

    mainWndControls->push_back(btn);

    GUI::controls.push_back(mainWnd);
}

void ThreadWorker(LPVOID par) {
    OutputDebugStringA("\nEnter to worker\n");

    try
    {
        GUI::Setup();
        Hooks::Setup();

        SetupGUI();
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
    auto str = StringFormat(std::string("Incoming message: %d\n"), ul_reason_for_call);
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
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        OutputDebugString(L"Exit from multiplayer.dll\n");
        break;
    }
    return TRUE;
}

