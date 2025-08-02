#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <regex>
#include <chrono>
#include <ctime>
#include <vector>

#include "../include/logger.h"

namespace
{
    inline const char *toUser(Elvl level)
    {
        switch (level)
        {
        case Elvl::eError:
            return "ERROR";
        case Elvl::eWarn:
            return "WARN";
        case Elvl::eAlways:
            return "LOG";
        case Elvl::eInfo:
            return "INFO";
        case Elvl::eSummary:
            return "SUMMARY";
        case Elvl::eDetails:
            return "DETAILS";
        case Elvl::eDebug:
            return "DEBUG";
        case Elvl::eFull:
            return "FULL";
        default:
            return "UNKNOWN";
        }
    }
}

std::mutex Logger::s_logMutex;

Logger::Logger() = default;

Logger &Logger::instance()
{
    static Logger logger;
    return logger;
}

void Logger::logMessage(Elvl elevel,
                        const char *cpFile,
                        int ciLine,
                        const char *cpfunc,
                        const char *cpfmt, ...)
{
    if (elevel > s_eRuntimeLogLevel)
    {
        return;
    }

    std::lock_guard<std::mutex> lock(s_logMutex);
    std::string timestamp = getTimeStamp("%Y-%m-%d %T");

    va_list args;
    va_start(args, cpfmt);
    std::string strMessage = formatMessage(cpfmt, args);
    va_end(args);

    strMessage = formatLogMessage(timestamp, toUser(elevel), cpFile, ciLine, cpfunc, strMessage);

    s_recentLogs.push_back(EString(strMessage));
    if (s_recentLogs.size() > s_maxRecentLogs)
        s_recentLogs.pop_front();
    printConsole(strMessage);

    auto strLogPath = prepareLogFile();
    if (!strLogPath.empty())
    {
        writeToFile(strLogPath, strMessage);
    }
}

void Logger::logMessage(Elvl level,
                        const char *file,
                        int line,
                        const char *func,
                        const EString &msg)
{
    logMessage(level, file, line, func, msg.data());
}

std::deque<EString> &Logger::getRecentLogs()
{
    std::lock_guard<std::mutex> lock(s_logMutex);
    return s_recentLogs;
}

void Logger::clearRecentLogs()
{
    std::lock_guard<std::mutex> lock(s_logMutex);
    s_recentLogs.clear();
}

void Logger::setCurrentLogLevel(const Elvl elevel)
{
    s_eRuntimeLogLevel = elevel;
}

Elvl Logger::getCurrentLogLevel()
{
    return s_eRuntimeLogLevel;
}

std::string Logger::formatMessage(const char *fmt, va_list args)
{
    va_list args_copy;
    va_copy(args_copy, args);
    int msg_size = vsnprintf(nullptr, 0, fmt, args_copy);
    va_end(args_copy);

    std::string message;
    if (msg_size > 0)
    {
        message.resize(msg_size + 1);
        vsnprintf(&message[0], message.size(), fmt, args);
        message.resize(msg_size);
    }
    return message;
}

std::string Logger::formatLogMessage(std::string &cstrTimestamp,
                                     const char *cclevel,
                                     const char *ccfile,
                                     int iLine,
                                     const char *ccfunc,
                                     const std::string &cstrMessage)
{
    // E.g. output [2025-05-26 15:51:46] [main.cpp:24] [LOG] testFunction - LOG function try out
    const char *filename = filename_from_path(ccfile);
    std::ostringstream oss;

    oss << "[" << cstrTimestamp << "] "
        << "[" << filename << ":" << iLine << "] "
        << "[" << cclevel << "] "
        << ccfunc;

    if (!cstrMessage.empty())
        oss << " - " << cstrMessage;
    oss << std::endl;

    return oss.str();
}

void Logger::printConsole(const std::string &cstrMessage)
{
    std::printf(cstrMessage.c_str());
    std::fflush(stdout);
}

void Logger::writeToFile(const std::filesystem::path &coPath, const std::string &cstrMessage)
{
    std::ofstream ofLogFile(coPath, std::ios::app);
    if (ofLogFile)
    {
        ofLogFile << cstrMessage.c_str();
    }
}

const char *Logger::filename_from_path(const char *cPath)
{
    const char *file = std::strrchr(cPath, '/');
    const char *alt = std::strrchr(cPath, '\\');
    file = std::max(file, alt);
    return file ? file + 1 : cPath;
}

std::filesystem::path Logger::prepareLogFile()
{
    try
    {
        std::filesystem::create_directories(s_cstrLogDir);
        auto oLogPath = getLogPath();

        if (std::filesystem::exists(oLogPath) && std::filesystem::file_size(oLogPath) > s_ciMaxLogSize)
        {
            rotateLog(oLogPath);
        }

        return oLogPath;
    }
    catch (...)
    {
        return {};
    }
}

std::filesystem::path Logger::getLogPath()
{
    return std::filesystem::path(s_cstrLogDir) / (getTimeStamp("%d_%m_%y") + ".log");
}

const std::string Logger::getTimeStamp(const std::string cstrTimeFormat)
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;

#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::vector<char> buffer(100);
    if (std::strftime(buffer.data(), buffer.size(), cstrTimeFormat.c_str(), &tm))
    {
        return std::string(buffer.data());
    }
    else
    {
        return std::string();
    }
}

void Logger::rotateLog(const std::filesystem::path &coLogPath)
{
    try
    {
        if (!std::filesystem::exists(coLogPath))
            return;

        std::string strBasename = coLogPath.stem().string();
        int max_num = 0;

        for (const auto &entry : std::filesystem::directory_iterator(s_cstrLogDir))
        {
            std::string strName = entry.path().filename().string();
            std::regex oPattern(strBasename + R"(\.lo(\d+))");
            std::smatch oMatch;
            if (std::regex_search(strName, oMatch, oPattern))
            {
                int num = std::stoi(oMatch[1].str());
                max_num = std::max(max_num, num);
            }
        }

        std::filesystem::path new_name = std::filesystem::path(s_cstrLogDir) / (strBasename + ".lo" + std::to_string(max_num + 1));
        std::filesystem::rename(coLogPath, new_name);
    }
    catch (...)
    {
    }
}

ScopeLogger::ScopeLogger(const char *file, int line, const char *func)
    : file_(file), line_(line), func_(func)
{
    Logger::instance().logMessage(Elvl::eFull, file_, line_, func_, ">> ENTER");
}

ScopeLogger::~ScopeLogger() noexcept
{
    Logger::instance().logMessage(Elvl::eFull, file_, line_, func_, "<< EXIT");
}