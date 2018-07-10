// SimpleLoggerTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SimpleLogger.h"


int main()
{
    std::unique_ptr<SimpleLogger> pLog(::CreateSimpleLogger(std::wstring(L"testLog.log")));

    for (size_t i = 0; i < 10; i++)
    {
        pLog->Log(L"Hello", 145, L"mama", i);
    }

    return 0;
}

