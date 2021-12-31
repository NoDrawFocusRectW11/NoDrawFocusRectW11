#include <windows.h>

// Thank you https://github.com/mrexodia/NoFlashWindow for providing this template

static void DisableDrawFocusRect()
{
    HINSTANCE hUser32 = GetModuleHandleW(L"user32.dll");
    if (!hUser32)
    {
        OutputDebugStringW(L"[NoDrawFocusRect] GetModuleHandleW failed for user32.dll...");
        return;
    }

    PVOID pDrawFocusRect = (PVOID)GetProcAddress(hUser32, "DrawFocusRect");
    if (pDrawFocusRect)
    {
        BYTE ret[] = { 0xC3, 0x00 };
        if (WriteProcessMemory(GetCurrentProcess(), pDrawFocusRect, ret, sizeof(ret), NULL))
            OutputDebugStringW(L"[NoDrawFocusRect] DrawFocusRect disabled!");
        else
            OutputDebugStringW(L"[NoDrawFocusRect] WriteProcessMemory failed for DrawFocusRect...");
    }
    else
        OutputDebugStringW(L"[NoDrawFocusRect] GetProcAddress failed for DrawFocusRect...");
}

extern "C" __declspec(dllexport) BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableDrawFocusRect();
        break;
    }
    return TRUE; // succesful
}