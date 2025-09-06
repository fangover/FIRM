#ifndef E071AFA1_4B42_42C4_8D5E_7747E28860A3
#define E071AFA1_4B42_42C4_8D5E_7747E28860A3

#include <atomic>
#include <functional>
#include <mutex>
#include <unordered_map>

template <typename... Args>
class EObserver
{
public:
    using ObserverID = uint64_t;
    using Callback = std::function<void(Args...)>;

    EObserver() = default;
    ~EObserver() = default;

    ObserverID subscribe(Callback callback)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        ObserverID id = ++mNextId;
        mlstObservers[id] = std::move(callback);
        return id;
    }

    void unsubscribe(ObserverID id)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        mlstObservers.erase(id);
    }

    bool isActive(ObserverID id) const
    {
        std::lock_guard<std::mutex> lock(mMutex);
        return mlstObservers.find(id) != mlstObservers.end();
    }

    void notify(Args... args) const
    {
        std::unordered_map<ObserverID, Callback> lstObserversCopy;
        {
            std::lock_guard<std::mutex> lock(mMutex);
            lstObserversCopy = mlstObservers;
        }
        for (const auto& [id, callback] : lstObserversCopy)
        {
            if (callback)
            {
                callback(args...);
            }
        }
    }

private:
    mutable std::mutex mMutex;
    std::unordered_map<ObserverID, Callback> mlstObservers;
    std::atomic<ObserverID> mNextId{ 0 };
};

#endif /* E071AFA1_4B42_42C4_8D5E_7747E28860A3 */
