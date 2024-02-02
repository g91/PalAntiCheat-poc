#include "pch.h"
#include "config.h"
#include <algorithm>

config Config;
void config::Init()
{
    //register hook
    Config.ClientBase = (DWORD64)GetModuleHandleA(0);
}
