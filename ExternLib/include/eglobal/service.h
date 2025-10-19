#ifndef C561B81F_EE51_46F8_B238_8FB7EF3C127C
#define C561B81F_EE51_46F8_B238_8FB7EF3C127C
// HybridRegistry.h
#pragma once
#include "registry.h"
#include "singleton.h"

namespace EGlobal
{
    class Service
    {
    public:
        template <typename T, typename... Args>
        static std::shared_ptr<T> instancePtr(Args&&... args)
        {
            auto existing = Registry::get<T>();
            if (existing)
            {
                return std::static_pointer_cast<T>(existing);
            }

            // Create singleton
            T& obj = Singleton<T>::instance(std::forward<Args>(args)...);

            // Wrap in shared_ptr with no-op deleter
            auto sp = std::shared_ptr<T>(&obj, [](T*) {});
            Registry::registerInstance<T>(sp);
            return sp;
        }

        template <typename T, typename... Args>
        static T& instance(Args&&... args)
        {
            return *instancePtr<T>(std::forward<Args>(args)...);
        }

        template <typename T>
        static void reset()
        {
            Singleton<T>::reset();
            std::lock_guard<std::mutex> lock(m_mutex);
            m_registry.erase(typeid(T));
        }

    private:
        static inline std::mutex m_mutex;
        static inline std::unordered_map<std::type_index, std::shared_ptr<void>> m_registry;
    };
}; // namespace EGlobal

#endif /* C561B81F_EE51_46F8_B238_8FB7EF3C127C */
