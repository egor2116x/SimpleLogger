#include "stdafx.h"
#include "App.h"
#include <iomanip>
App::App()
{
    m_commandsMap.insert(std::make_pair(L"filepath", COMMANDS::FILEPATH));
    m_commandsMap.insert(std::make_pair(L"parse", COMMANDS::PARSE));
    m_commandsMap.insert(std::make_pair(L"print", COMMANDS::PRINT));
    m_commandsMap.insert(std::make_pair(L"help", COMMANDS::HELP));
    m_commandsMap.insert(std::make_pair(L"exit", COMMANDS::EXIT));
    m_parser.reset(::CreateParser());
}

void App::Run()
{
    std::wstring userInput;
    std::wcout << ">";
    std::getline(std::wcin, userInput);
    ParseUserInput(userInput);
    while (m_currentCommand != COMMANDS::EXIT)
    {
        switch (m_currentCommand)
        {
            case COMMANDS::FILEPATH :
                m_parser->SetFilePath(m_currentArgument);
                break;
            case COMMANDS::PARSE: 
                m_parser->Parse();
                break;
            case COMMANDS::PRINT: 
                m_parser->Print();
                break;
            case COMMANDS::HELP:
                printHelp();
                break;
            default:
                std::wcout << L"unknown command" << std::endl;
        }

        m_currentCommand = COMMANDS::NONE;
        m_currentArgument.clear();

        std::wcout << ">";
        std::wcin >> userInput;
        ParseUserInput(userInput);
    }
   
}

void App::ParseUserInput(const std::wstring & userInput)
{
    std::wstringstream ss;
    ss << userInput;
    std::wstring tmp;
    std::vector<std::wstring> buff;
    while (ss >> tmp)
    {
        buff.push_back(tmp);
    }

    if (buff.size() > 0)
    {
        m_currentCommand = FindInCommandsMap(buff[0]);
        if (m_currentCommand == COMMANDS::FILEPATH)
        {
            m_currentArgument = (buff.size() > 1 ? buff[1] : L"");
        }
    }
}

App::COMMANDS App::FindInCommandsMap(const std::wstring & userInput)
{
    for (auto it = m_commandsMap.begin(); it != m_commandsMap.end(); ++it)
    {
        if (it->first.compare(userInput) == 0)
        {
            return it->second;
        }
    }
    return COMMANDS::NONE;
}

void App::printHelp() const
{
    for (auto obj : m_commandsMap)
    {
        switch (obj.second)
        {
        case COMMANDS::FILEPATH:
            std::wcout << std::setw(20) << L"filepath <path to file> - set path to file" << std::endl;
            break;
        case COMMANDS::PARSE:
            std::wcout << L"parse - load data from set file" << std::endl;
            break;
        case COMMANDS::PRINT:
            std::wcout << L"print - print data to console" << std::endl;
            break;
        case COMMANDS::HELP:
            std::wcout << L"help - help" << std::endl;
            break;
        case COMMANDS::EXIT:
            std::wcout << L"exit - exit from program" << std::endl;
            break;
        }
    }
}
