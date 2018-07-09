// SimpleLoggerApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SimpleLogger.h"


int main()
{
    std::unique_ptr<SimpleLogger> pLog(::CreateSimpleLogger(std::wstring(L"testLog.log")));

    pLog->Log(L"Hello", 145, L"mama", 13);
    std::cin.get();
    return 0;
}

