#ifndef EXTERNAL_LIB_FILESTREAM_INCLUDE_FILESTREAMHANDLE_H
#define EXTERNAL_LIB_FILESTREAM_INCLUDE_FILESTREAMHANDLE_H
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace FileStream
{
    constexpr char Endl[] = "\n";
    constexpr char Tab[] = "\t";
    class FileHandle
    {
    public:
        explicit FileHandle(const std::string& cstrName, std::ios::openmode mode = std::ios::app);

        ~FileHandle();

        void readFile() const;
        void clearFile() const;

        template <typename T>
        FileHandle& operator<<(T&& content)
        {
            if (m_ofsFile.is_open())
            {
                m_ofsFile << std::forward<T>(content);
            }
            return *this;
        }

        // Variadic template version
        template <typename... Args>
        void appendFile(Args&&... args)
        {
            if (m_ofsFile.is_open())
            {
                ((m_ofsFile << std::forward<Args>(args)), ...);
            }
        }

        // Batch version for containers
        template <typename Container>
        void appendFile(const Container& lines)
        {
            if (m_ofsFile.is_open())
            {
                for (const auto& line : lines)
                {
                    m_ofsFile << line << '\n';
                }
            }
        }

    private:
        std::string m_strFileName;
        mutable std::ofstream m_ofsFile;
    };

} // namespace FileStream
#endif // EXTERNAL_LIB_FILESTREAM_INCLUDE_FILESTREAMHANDLE_H