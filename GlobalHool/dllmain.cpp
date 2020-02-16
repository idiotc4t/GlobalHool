// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
HMODULE g_hModule = NULL;
HHOOK g_hHook = NULL;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_hModule = hModule;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

LRESULT MyFunction(int code,WPARAM wParam,LPARAM lParam) {
    MessageBox(0, 0, 0, 0);
    return CallNextHookEx(g_hHook, code, wParam, lParam);
}

EXTERN_C __declspec(dllexport) BOOL SetGlobalHook() {
    g_hHook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)MyFunction, g_hModule,0);
    if (!g_hHook)
    {
        return FALSE;
    }
    return TRUE;
}

EXTERN_C __declspec(dllexport) BOOL UnsetGlobalHook() {
    if (g_hHook)
    {
        UnhookWindowsHookEx(g_hHook);
    }
    return TRUE;
}