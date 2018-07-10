// SimpleLoggerApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "App.h"


int main(int argc, char *argv[])
{
    App app;
    try
    {
        app.Run();
    }
    catch (...)
    {
        std::wcout << "something happened !" << std::endl;
    }

    std::wcin.get();
    return 0;
}

