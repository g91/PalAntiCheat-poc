#pragma once
#include "pch.h"
#include "initialize.hpp"

using namespace SDK;

extern DWORD WINAPI MainThread_Initialize();
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dwCallReason, LPVOID lpReserved)
{
    switch (dwCallReason) {
        case (DLL_PROCESS_ATTACH): {
            config::Init();
            InitGObjects();
            DisableThreadLibraryCalls(hModule);
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread_Initialize, hModule, NULL, NULL);
            break;
        }
        case (DLL_PROCESS_DETACH): {
            break;
        }
    }
    return TRUE;
}