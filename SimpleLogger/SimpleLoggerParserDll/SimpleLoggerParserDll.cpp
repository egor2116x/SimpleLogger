#include "stdafx.h"
#include "SimpleLoggerParserDll.h"

Parser::Parser(const std::wstring & inFilePath) : m_fileName(inFilePath)
{
    if (!m_fileName.empty())
    {
        m_in.open(m_fileName.c_str());
    }
}