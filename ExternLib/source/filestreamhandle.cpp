
#include "../include/log.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "eresult.h"
#include "filestreamhandle.h"

using namespace FileStream;

FileHandle::FileHandle(const std::string& cstrName, std::ios::openmode mode) : m_strFileName(cstrName)
{
    std::filesystem::path oFilePath(cstrName);
    auto oParentDir = oFilePath.parent_path();

    // Ensure diretory existed
    if (!oParentDir.empty() && !std::filesystem::exists(oParentDir))
    {
        std::filesystem::create_directories(oParentDir);
    }

    m_ofsFile.open(cstrName, mode);
    LOG_IF_FAILED(m_ofsFile.is_open(), "Error opening file: ", cstrName.c_str());
}

FileHandle::~FileHandle()
{
    LOG_ENTRY;

    if (m_ofsFile)
    {
        m_ofsFile.close();
    }
}

EResult FileHandle::readFile() const
{
    LOG_ENTRY;

    std::string content;
    TRY(getContent(content));
    LOG(content);

    return EResult::ok();
}

void FileHandle::clearFile() const
{
    LOG_ENTRY;

    std::ofstream ofs;
    ofs.open(m_strFileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

EResult FileHandle::getContent(std::string& content) const
{
    LOG_ENTRY;

    if (m_ofsFile.is_open())
    {
        m_ofsFile.flush();
    }

    std::ifstream inFile(m_strFileName, std::ios::in | std::ios::binary);
    TRY(inFile.is_open(), "File not open!");

    std::ostringstream ss;
    ss << inFile.rdbuf();
    content = ss.str();
    inFile.close();

    return EResult::ok();
}
