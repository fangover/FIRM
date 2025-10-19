#ifndef LOG_H
#define LOG_H

#include <optional>

#include "eresult.h"
#include "logger.h"

namespace
{
    template <typename T>
    inline std::optional<EResult> checkResult(const T& result,
                                              const char* file,
                                              int line,
                                              const char* func,
                                              const char* msg = nullptr)
    {
        if constexpr (std::is_same_v<T, EResult>)
        {
            if (result.isFail())
            {
                Logger::instance().logMessage(Elvl::eError, file, line, func, msg ? msg : result.error());
                return result; // propagate
            }
        }
        else if constexpr (std::is_same_v<T, bool>)
        {
            if (!result)
            {
                Logger::instance().logMessage(Elvl::eError, file, line, func, msg ? msg : "Condition failed");
                return EResult::fail(msg ? msg : "Condition failed");
            }
        }
        return std::nullopt; // success
    }
} // namespace

// Logging Macros
#define LOG_ENTRY                                                                                                      \
    []                                                                                                                 \
    {                                                                                                                  \
        ScopeLogger __scope_logger__(__FILE__, __LINE__, __func__);                                                    \
    }()

#define LOG(...) Logger::instance().logMessage(Elvl::eAlways, __FILE__, __LINE__, __func__ __VA_OPT__(, ) __VA_ARGS__)

#define LOG_ERROR(...)                                                                                                 \
    Logger::instance().logMessage(Elvl::eError, __FILE__, __LINE__, __func__ __VA_OPT__(, ) __VA_ARGS__)

#define LOG_WARNING(...)                                                                                               \
    Logger::instance().logMessage(Elvl::eWarn, __FILE__, __LINE__, __func__ __VA_OPT__(, ) __VA_ARGS__)

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

#define TRY(expr, ...)                                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        auto _tmp = (expr);                                                                                            \
        if (auto _err = checkResult(_tmp, __FILE__, __LINE__, __func__ __VA_OPT__(, ) __VA_ARGS__))                    \
            return *_err;                                                                                              \
    } while (0)

#define FATAL_CHECK(cond, ...)                                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(cond))                                                                                                   \
        {                                                                                                              \
            if constexpr (sizeof(#__VA_ARGS__) > 1)                                                                    \
            {                                                                                                          \
                Logger::instance().logMessage(Elvl::eFatal, __FILE__, __LINE__, __func__, ##__VA_ARGS__);              \
            }                                                                                                          \
            else                                                                                                       \
            {                                                                                                          \
                Logger::instance().logMessage(                                                                         \
                    Elvl::eFatal, __FILE__, __LINE__, __func__, "Fatal check failed: " #cond);                         \
            }                                                                                                          \
            std::abort();                                                                                              \
        }                                                                                                              \
    } while (0)

#endif // LOG_H