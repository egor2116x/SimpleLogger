#pragma once

#include "stdafx.h"

#if defined(SIMPLELOGGERPARSERDLL_EXPORTS) 
#   define LOGGERPARSER_API   __declspec(dllexport)
#else 
#   define LOGGERPARSER_API   __declspec(dllimport)
#endif  

using ItemLogger = std::vector < std::wstring >;
using wStrSizeType = std::wstring::size_type;

class Parser
{
    public:
        Parser(const std::wstring & inFilePath);
        bool Parse();
        void Print();
        std::vector<ItemLogger> & GetDataBase() { return m_dataBase; }
    private:
        std::wstring m_fileName;
        std::wifstream m_in;
        std::vector<ItemLogger> m_dataBase;
};

inline bool Parser::Parse()
{
    if (m_in.is_open())
    {
        std::wstring buff;
        while (std::getline(m_in, buff))
        {
            m_dataBase.push_back(ItemLogger());
            wStrSizeType pos = buff.find(L'[');
            if (pos != std::wstring::npos)
            {
                buff = buff.substr(pos + 1, buff.size() - pos);
            }
            std::wstring tmp;
            while (pos != std::wstring::npos)
            {
                pos = buff.find(L',');
                if (pos != std::wstring::npos)
                {
                    tmp = buff.substr(0, pos);
                    buff = buff.substr(pos + 1, buff.size() - pos);
                    m_dataBase[m_dataBase.size() - 1].push_back(tmp);
                }
                else
                {
                    pos = std::wstring::npos;
                }                 
            }
        }
    }
    else
    {
        return false;
    }

    if (m_dataBase.empty())
    {
        return false;
    }

    return true;
}

inline void Parser::Print()
{
    for (auto it = m_dataBase.begin(); it != m_dataBase.end(); ++it) {
        for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
            std::wcout << *it2 << " ";
        }
        std::wcout << std::endl;
    }
}

extern "C" LOGGERPARSER_API Parser * APIENTRY CreateParser(const std::wstring & fileName);
