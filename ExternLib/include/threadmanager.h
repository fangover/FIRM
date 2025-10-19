#ifndef AEC5D79C_15F1_4676_A25D_DD5D394E9F9E
#define AEC5D79C_15F1_4676_A25D_DD5D394E9F9E

#include <functional>
#include <map>
#include <mutex>
#include <thread>
#include <typeindex>

#include "estring.h"
#include "log.h"
#include "logger.h"

class ThreadManager
{
public:
    ThreadManager() = default;
    ~ThreadManager()
    {
        stopAll();
        std::lock_guard<std::mutex> lock(m_mutex);
        m_threads.clear();
        m_tasks.clear();
    }

    template <typename T>
    void add(std::function<void(std::stop_token)> func)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::type_index typeId(typeid(T));

        if (m_threads.count(typeId))
        {
            LOG_LEVEL(Elvl::eError, EString::sprintf("Thread for type %s already exists.", typeid(T).name()));
            return;
        }

        m_tasks[typeId] = func;
    }

    void startAll()
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        for (auto& [typeId, func] : m_tasks)
        {
            LOG_LEVEL(Elvl::eAlways, EString::sprintf("Starting thread: %s", typeId.name()));
            m_threads[typeId] = std::jthread(
                [func](std::stop_token stoken)
                {
                    try
                    {
                        func(stoken);
                    }
                    catch (const std::exception& e)
                    {
                        LOG_LEVEL(Elvl::eError,
                                  EString::sprintf("Exception in thread %s : %s", typeid(func).name(), e.what()));
                    }
                });
        }
    }

    void stopAll()
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        LOG_LEVEL(Elvl::eAlways, "Stopping all threads...");
        for (auto& [_, t] : m_threads)
        {
            t.request_stop(); // cooperative stop signal
        }
    }

    template <typename T>
    void stop()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::type_index typeId(typeid(T));
        if (auto it = m_threads.find(typeId); it != m_threads.end())
        {
            LOG_LEVEL(Elvl::eAlways, EString::sprintf("Stopping threads...", typeId.name()));
            it->second.request_stop();
        }
    }

    void joinAll()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        LOG_LEVEL(Elvl::eAlways, "Waiting for threads to finish...");
        m_threads.clear();
    }

private:
    std::map<std::type_index, std::function<void(std::stop_token)>> m_tasks;
    std::map<std::type_index, std::jthread> m_threads;
    std::mutex m_mutex;
};

#endif /* AEC5D79C_15F1_4676_A25D_DD5D394E9F9E */
