#ifndef LOG_H
#define LOG_H

#include "logger.h"

// Logging Macros
#define LOG_ENTRY                                                                                                      \
    []                                                                                                                 \
    {                                                                                                                  \
        ScopeLogger __scope_logger__(__FILE__, __LINE__, __func__);                                                    \
    }()

#define LOG(...) Logger::instance().logMessage(Elvl::eAlways, __FILE__, __LINE__, __func__ __VA_OPT__(, ) __VA_ARGS__)

#define LOG_IF_FAILED(cond, ...)                                                                                       \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(cond))                                                                                                   \
        {                                                                                                              \
            Logger::instance().logMessage(Elvl::eError, __FILE__, __LINE__, __func__ __VA_OPT__(, ) __VA_ARGS__);      \
        }                                                                                                              \
    } while (0)

#define LOG_LEVEL(elevel, ...)                                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        Logger::instance().logMessage(elevel, __FILE__, __LINE__, __func__, ##__VA_ARGS__);                            \
    } while (0)

#define TRY(cond)                                                                                                      \
    if (!(cond))                                                                                                       \
    {                                                                                                                  \
        Logger::instance().logMessage(Elvl::eError, __FILE__, __LINE__, __func__, "Condition failed: " #cond);         \
        return;                                                                                                        \
    }

#define TRY_MSG(cond, ...)                                                                                             \
    if (!(cond))                                                                                                       \
    {                                                                                                                  \
        Logger::instance().logMessage(Elvl::eError, __FILE__, __LINE__, __func__, __VA_ARGS__);                        \
        return;                                                                                                        \
    }

#define TRY_VAL(cond, ret, ...)                                                                                        \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(cond))                                                                                                   \
        {                                                                                                              \
            Logger::instance().logMessage(Elvl::eError, __FILE__, __LINE__, __func__, ##__VA_ARGS__);                  \
            return ret;                                                                                                \
        }                                                                                                              \
    } while (0)

#define FATAL_CHECK(cond, ...)                                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(cond))                                                                                                   \
        {                                                                                                              \
            Logger::instance().logMessage(Elvl::eFatal, __FILE__, __LINE__, __func__, ##__VA_ARGS__);                  \
            std::abort();                                                                                              \
        }                                                                                                              \
    } while (0)

#endif // LOG_H