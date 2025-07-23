#ifndef E414D4C7_ACF7_4E46_9161_272AA996AAF6
#define E414D4C7_ACF7_4E46_9161_272AA996AAF6

#include <memory>
#include <mutex>
#include <utility>

template <typename T>
class ESingleton
{
public:
    template <typename... Args>
    static T &instance(Args &&...args)
    {
        std::call_once(mOnceFlag, [&]()
                       { mInstance = std::make_unique<T>(std::forward<Args>(args)...); });
        return *mInstance;
    }

    static bool is_initialized()
    {
        return mInstance != nullptr;
    }

    static void reset()
    {
        std::lock_guard<std::mutex> lock(mMutex);
        mInstance.reset();
        mOnceFlag = std::once_flag();
    }

private:
    ESingleton() = delete;
    ~ESingleton() = delete;
    ESingleton(const ESingleton &) = delete;
    ESingleton &operator=(const ESingleton &) = delete;

    static inline std::unique_ptr<T> mInstance = nullptr;
    static inline std::once_flag mOnceFlag;
    static inline std::mutex mMutex;
};

#endif /* E414D4C7_ACF7_4E46_9161_272AA996AAF6 */
