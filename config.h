#pragma once
#include <Windows.h>
#include "SDK.hpp"

class config
{
public:
	//offsets
	DWORD64 ClientBase = 0;

	//static function
	static void Init();
};
extern config Config;
