#pragma once

#include "stdafx.h"

#if defined(SIMPLELOGGER_EXPORTS) 
#   define LOGGER_API   __declspec(dllexport)
#else 
#   define LOGGER_API   __declspec(dllimport)
#endif 

class SimpleLogger
{
    public:
        SimpleLogger(const std::wstring & fileName);
        void SetLogFileName(const std::wstring & fileName) { m_filePath = fileName; }
        const std::wstring & GetLogFileName() const { return m_filePath; }
        template<typename Arg, typename ... Args>
        void Log(Arg &&, Args &&...);
        template<typename Arg, typename ... Args>
        void LogIf(bool, Arg &&, Args &&...);
    private:
        std::wstring m_filePath;
        std::wofstream m_out;
        std::mutex m_mtx;
};

template<typename Arg, typename ... Args>
inline void SimpleLogger::Log(Arg && arg, Args &&... args)
{
    if (m_out.is_open())
    {
        std::time_t t = std::time(nullptr);
        std::tm * _tm = std::localtime(&t);
        std::wstring tmp;
        std::wstring  bufftime = std::to_wstring(_tm->tm_year + 1900);
                      tmp = std::to_wstring(_tm->tm_mon + 1);
                      bufftime += L" " + (tmp.size() == 1 ? L"0" + tmp : tmp);
                      tmp = std::to_wstring(_tm->tm_mday);
                      bufftime += L" " + (tmp.size() == 1 ? L"0" + tmp : tmp);

        std::lock_guard<std::mutex> lock(m_mtx);
        m_out << L"["
            << bufftime << L','
            << static_cast<unsigned>(GetCurrentProcessId()) << L','
            << static_cast<unsigned>(GetCurrentThreadId())  << L','
            << std::forward<Arg>(arg);
        using expander = int[];
        (void)expander {
            0, (void(m_out << ',' << std::forward<Args>(args)), 0)...
        };
        m_out << L"]" << std::endl;
    }
}

template<typename Arg, typename ...Args>
inline void SimpleLogger::LogIf(bool condition, Arg && arg, Args && ... args)
{
    if (condition)
    {
        Log(arg, args);
    }
}

extern "C" LOGGER_API SimpleLogger * APIENTRY CreateSimpleLogger(const std::wstring & fileName);


