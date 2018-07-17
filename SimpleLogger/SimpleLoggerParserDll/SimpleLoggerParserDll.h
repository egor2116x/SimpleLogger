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
        bool Parse();
        void Print();
        void SetFilePath(const std::wstring & filePath) { m_fileName = filePath; }
        const std::wstring & GetFilePath() const { return m_fileName; }
        std::vector<ItemLogger> & GetDataBase() { return m_dataBase; }
    private:
        int GetOffset(const std::wstring & str);
    private:
        std::wstring m_fileName;
        std::wifstream m_in;
        std::vector<ItemLogger> m_dataBase;
};

inline bool Parser::Parse()
{
        if (m_fileName.empty())
        {
            return false;
        }

        m_in.open(m_fileName.c_str(), std::ios::app);
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


    if (m_dataBase.empty())
    {
        return false;
    }

    return true;
}

inline void Parser::Print()
{
    std::sort(m_dataBase.begin(), m_dataBase.end());
    int offset = 1;

    for (size_t i = 0; i < m_dataBase.size(); ++i) {
        offset = GetOffset(m_dataBase[i][0]);
        offset = (offset % 1000 - 10 <= 0 ? 1 : offset % 1000 - 10);
        for (size_t j = 0; j < m_dataBase[i].size(); j++) {
            std::wcout << std::setw(1);
            if (j == 0)
                std::wcout <<  L"Date      ";
            else if(j == 1)
                std::wcout <<  L"Process ID";
            else if(j == 2)
                std::wcout << L"Thread ID ";
            
            std::wcout << std::setw(static_cast<int>(offset));
            if (j > 2)
                std::wcout << std::setw(static_cast<int>(offset + 10));

            std::wcout << m_dataBase[i][j] << std::endl;
        }
        std::wcout << std::endl;
    }
}

inline int Parser::GetOffset(const std::wstring & str)
{
    std::wstringstream ss;
    std::wstring tmp;
    int result = 1;
    ss << str;
    while (ss >> tmp)
    {
        result += std::stoi(tmp);
    }
    return (result <= 0 ? 1 : result);
}

extern "C" LOGGERPARSER_API Parser * APIENTRY CreateParser();
