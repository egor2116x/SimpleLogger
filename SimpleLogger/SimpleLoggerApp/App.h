#pragma once
#include "stdafx.h"
#include "SimpleLoggerParserDll.h"

class App
{
    public:
        App();
        enum class COMMANDS { FILEPATH, PARSE, PRINT, EXIT, HELP, NONE };
        using CommandsMap = std::map<std::wstring, COMMANDS>;
        void Run();
    private:
        void ParseUserInput(const std::wstring & userInput);
        COMMANDS FindInCommandsMap(const std::wstring & userInput);
        void printHelp() const;
    private:
        COMMANDS m_currentCommand;
        std::wstring m_currentArgument;
        std::unique_ptr<Parser> m_parser;
        CommandsMap m_commandsMap;
};

