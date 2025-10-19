#ifndef EC041CB6_6FF5_45E9_9157_0C2F01B0A805
#define EC041CB6_6FF5_45E9_9157_0C2F01B0A805
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>

namespace EString
{
    template <typename... Args>
    std::string sprintf(const std::string& fmt, Args&&... args)
    {
        int size = std::snprintf(nullptr, 0, fmt.c_str(), std::forward<Args>(args)...) + 1;
        if (size <= 0)
        {
            throw std::runtime_error("Formatting error");
        }

        std::unique_ptr<char[]> buf(new char[size]);
        std::snprintf(buf.get(), size, fmt.c_str(), std::forward<Args>(args)...);
        return std::string(buf.get(), buf.get() + size - 1);
    }
} // namespace EString

template <typename E>
struct ToUserImpl
{
    static std::string convert(E)
    {
        static_assert(sizeof(E) == 0, "toUser not implemented for this enum type");
        return "";
    }
};

template <typename E>
std::string toUser(E e)
{
    return ToUserImpl<E>::convert(e);
}

#define DEFINE_ENUM(EnumType, ...)                                                                                     \
    template <>                                                                                                        \
    struct ToUserImpl<EnumType>                                                                                        \
    {                                                                                                                  \
        static std::string convert(EnumType value)                                                                     \
        {                                                                                                              \
            switch (value)                                                                                             \
            {                                                                                                          \
                __VA_ARGS__                                                                                            \
                default: return "Unknown " #EnumType;                                                                  \
            }                                                                                                          \
        }                                                                                                              \
    }

#endif /* EC041CB6_6FF5_45E9_9157_0C2F01B0A805 */
