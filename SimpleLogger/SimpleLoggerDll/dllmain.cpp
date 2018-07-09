// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "SimpleLogger.h"

extern "C" LOGGER_API SimpleLogger * APIENTRY CreateSimpleLogger(const std::wstring & fileName) {
    return new SimpleLogger(fileName);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

