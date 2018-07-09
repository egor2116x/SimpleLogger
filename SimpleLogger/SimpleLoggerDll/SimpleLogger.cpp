// SimpleLogger.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "SimpleLogger.h"

SimpleLogger::SimpleLogger(const std::wstring & fileName) : m_filePath(fileName)
{
    if (!m_filePath.empty())
    {
        std::lock_guard<std::mutex> lock(m_mtx);
        m_out.open(m_filePath.c_str(), std::ios::app);
    }

}
