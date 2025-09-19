#ifndef B76F388E_B85C_46A0_9F66_DADA42108026
#define B76F388E_B85C_46A0_9F66_DADA42108026

#include <iostream>
#include <memory>
#include <mutex>
#include <typeindex>
#include <unordered_map>

class EGlobalRegistry
{
public:
    template <typename T, typename... Args>
    static std::shared_ptr<T> emplace(Args&&... args)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        auto instance = std::make_shared<T>(std::forward<Args>(args)...);
        mRegistry[typeid(T)] = instance;
        return instance;
    }

    template <typename T>
    static std::shared_ptr<T> get()
    {
        std::lock_guard<std::mutex> lock(mMutex);
        auto it = mRegistry.find(typeid(T));
        return it != mRegistry.end() ? std::static_pointer_cast<T>(it->second) : nullptr;
    }

    template <typename T>
    static void registerInstance(std::shared_ptr<T> instance)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        mRegistry[typeid(T)] = std::move(instance);
    }

private:
    static inline std::mutex mMutex;
    static inline std::unordered_map<std::type_index, std::shared_ptr<void>> mRegistry;
};

#endif /* B76F388E_B85C_46A0_9F66_DADA42108026 */
