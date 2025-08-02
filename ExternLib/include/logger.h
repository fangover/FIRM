#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <mutex>
#include <filesystem>
#include <cstdarg>
#include <deque>
#include "estring.h"

enum class Elvl : int
{
    eFatal = -3,
    eError = -2,
    eWarn = -1,
    eAlways = 0,
    eInfo = 1,
    eSummary = 2,
    eDetails = 3,
    eDebug = 4,
    eFull = 5
};

class Logger
{
public:
    Logger();
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
    Logger(Logger &&) = delete;
    Logger &operator=(Logger &&) = delete;

    static Logger &instance();

    static void logMessage(Elvl level,
                           const char *,
                           int,
                           const char *,
                           const char * = "", ...);
    static void logMessage(Elvl level,
                           const char *file,
                           int line,
                           const char *func,
                           const EString &msg);
    static std::deque<EString> &getRecentLogs();
    static void clearRecentLogs();

    static void setCurrentLogLevel(const Elvl);
    static Elvl getCurrentLogLevel();

private:
    static std::string formatMessage(const char *, va_list);
    static std::string formatLogMessage(std::string &,
                                        const char *,
                                        const char *,
                                        int,
                                        const char *,
                                        const std::string &);

    static void printConsole(const std::string &);
    static void writeToFile(const std::filesystem::path &, const std::string &);

    static const char *filename_from_path(const char *);
    static std::filesystem::path prepareLogFile();
    static std::filesystem::path getLogPath();

    static const std::string getTimeStamp(const std::string);
    static void rotateLog(const std::filesystem::path &);

    static std::mutex s_logMutex;
    static constexpr std::string_view s_cstrLogDir = "build/out/log";
    static constexpr size_t s_ciMaxLogSize = 5 * 1024 * 1024;

    static inline std::deque<EString> s_recentLogs;
    static constexpr size_t s_maxRecentLogs = 1000;

    static inline Elvl s_eRuntimeLogLevel = Elvl::eAlways;
};

class ScopeLogger
{
public:
    ScopeLogger(const char *, int, const char *);
    ~ScopeLogger() noexcept;

private:
    const char *file_;
    int line_;
    const char *func_;
};

#endif // LOGGING_H
