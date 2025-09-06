
#include "../include/log.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "../include/FileStreamHandle.h"

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

void FileHandle::readFile() const
{
    LOG_ENTRY;

    if (m_ofsFile.is_open())
    {
        m_ofsFile.flush(); // Ensure all buffered data is written
    }

    std::ifstream inFile(m_strFileName);
    TRY(inFile.is_open());

    std::string line;
    while (std::getline(inFile, line))
    {
        std::cout << line << std::endl;
    }
    inFile.close();
}

void FileHandle::clearFile() const
{
    LOG_ENTRY;

    std::ofstream ofs;
    ofs.open(m_strFileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}
