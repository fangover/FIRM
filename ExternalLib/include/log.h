#ifndef LOG_H
#define LOG_H

#include "logger.h"

enum class ELvl : int
{
    eNONE = 0,
    eINFO = 1,
    eSUMMARY = 2,
    eDETAILS = 3,
    eDEBUG = 4
};

constexpr ELvl LOGLEVEL = ELvl::eINFO;

// Logging Macros
// #define LOG_ENTRY ScopeLogger __scope_logger__(__FILE__, __LINE__, __func__)
#define LOG_ENTRY [] {                                \
    if (LOGLEVEL >= ELvl::eDEBUG)                    \
        ScopeLogger __scope_logger__(__FILE__, __LINE__, __func__); }()

#define LOG(...) Logger::instance().logMessage("LOG", __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define LOG_LEVEL(level, ...)                                                                   \
    do                                                                                          \
    {                                                                                           \
        if (LOGLEVEL >= level)                                                                  \
            Logger::instance().logMessage(#level, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)

#define LOG_IF_FAILED(cond, ...) \
    do                           \
    {                            \
        if (!(cond))             \
            LOG(__VA_ARGS__);    \
    } while (0)

#define TRY(cond, ...)                                                                         \
    do                                                                                         \
    {                                                                                          \
        if (!(cond))                                                                           \
        {                                                                                      \
            Logger::instance().logMessage("TRY", __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
            return;                                                                            \
        }                                                                                      \
    } while (0)

#define TRY_VAL(cond, ret, ...)                                                                \
    do                                                                                         \
    {                                                                                          \
        if (!(cond))                                                                           \
        {                                                                                      \
            Logger::instance().logMessage("TRY", __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
            return ret;                                                                        \
        }                                                                                      \
    } while (0)

#define FATAL_CHECK(cond, ...)                                                                   \
    do                                                                                           \
    {                                                                                            \
        if (!(cond))                                                                             \
        {                                                                                        \
            Logger::instance().logMessage("FATAL", __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
            std::abort();                                                                        \
        }                                                                                        \
    } while (0)

#endif // LOG_H