#include "pch.h"
#include "DefaultTypes.h"
#include <string>
#include <memory>

HANDLE hThread;
DWORD threadId;

template<typename ... Args>
std::string StringFormat(const std::string& format, Args ... args)
{
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size_s <= 0) return format;
    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

undefined4 FUN_0047ac10(void* _this, uint param_1, Point* param_2) {
    undefined4 (* func)(void*, uint, Point *) = (undefined4(*)(void*, uint, Point*))0x0047ac10;
 
    return func(_this, param_1, param_2);
}

void ThreadWorker(LPVOID par) {
    OutputDebugStringA("\nEnter to worker\n");

    while (true)
    {
        Sleep(100);

    }

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
        
        DisableThreadLibraryCalls(hModule);

        hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadWorker, NULL, NULL, &threadId);

        OutputDebugString(L"Test");
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        OutputDebugString(L"Exit from multiplayer.dll");
        break;
    }
    return TRUE;
}

