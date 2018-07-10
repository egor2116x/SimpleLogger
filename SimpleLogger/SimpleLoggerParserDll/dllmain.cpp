#include "stdafx.h"
#include "SimpleLoggerParserDll.h"

extern "C" LOGGERPARSER_API Parser * APIENTRY CreateParser(const std::wstring & fileName) {
    return new Parser(fileName);
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

