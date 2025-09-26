#ifndef E414D4C7_ACF7_4E46_9161_272AA996AAF6
#define E414D4C7_ACF7_4E46_9161_272AA996AAF6

#include <memory>
#include <mutex>
#include <utility>

namespace EGlobal
{
    template <typename T>
    class Singleton
    {
    public:
        template <typename... Args>
        static T& instance(Args&&... args)
        {
            std::call_once(m_onceFlag, [&]() { m_instance = std::make_unique<T>(std::forward<Args>(args)...); });
            return *m_instance;
        }

        static bool is_initialized() { return m_instance != nullptr; }

        static void reset()
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_instance.reset();
            m_onceFlag.~once_flag();
            new (&m_onceFlag) std::once_flag();
        }

    private:
        Singleton() = delete;
        ~Singleton() = delete;
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        static inline std::unique_ptr<T> m_instance = nullptr;
        static inline std::once_flag m_onceFlag;
        static inline std::mutex m_mutex;
    };
} // namespace EGlobal

#endif /* E414D4C7_ACF7_4E46_9161_272AA996AAF6 */
