#ifndef EC041CB6_6FF5_45E9_9157_0C2F01B0A805
#define EC041CB6_6FF5_45E9_9157_0C2F01B0A805
#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>
#include <utility>
#include <vector>
#include <regex>

class EString
{
    std::string m_value;

    template <typename... Args>
    std::string format(const std::string &fmt, Args &&...args)
    {
        size_t size = std::snprintf(nullptr, 0, fmt.c_str(), std::forward<Args>(args)...) + 1; // +1 for '\0'
        if (size <= 0)
            throw std::runtime_error("Format error");

        std::unique_ptr<char[]> buf(new char[size]);
        std::snprintf(buf.get(), size, fmt.c_str(), std::forward<Args>(args)...);
        return std::string(buf.get(), buf.get() + size - 1); // Exclude the null terminator
    }

public:
    EString() = default;
    EString(std::string str) : m_value(std::move(str)) {}
    EString(const char *str) : m_value(str ? str : "") {}

    EString(const EString &) = default;
    EString(EString &&) noexcept = default;
    EString &operator=(const EString &) = default;
    EString &operator=(EString &&) noexcept = default;

    template <typename... Args>
    EString &sprintf(const std::string &fmt, Args &&...args)
    {
        m_value = format(fmt, std::forward<Args>(args)...);
        return *this;
    }

    const char *c_str() const { return m_value.c_str(); }
    const char *data() const { return m_value.data(); }

    inline operator const std::string &() const { return m_value; }
    inline operator std::string_view() const { return m_value; }
};

template <typename T>
auto toStr(const T &value) -> decltype(std::ostringstream{} << value, EString{})
{
    std::ostringstream oss;
    oss << value;
    return EString{oss.str()};
}

template <typename E>
struct ToUserImpl
{
    static EString convert(E)
    {
        static_assert(sizeof(E) == 0, "toUser not implemented for this enum type");
        return "";
    }
};

template <typename E>
EString toUser(E e)
{
    return ToUserImpl<E>::convert(e);
}

#define DEFINE_ENUM(EnumType, ...)             \
    template <>                                \
    struct ToUserImpl<EnumType>                \
    {                                          \
        static EString convert(EnumType value) \
        {                                      \
            switch (value)                     \
            {                                  \
                __VA_ARGS__                    \
            default:                           \
                return "Unknown " #EnumType;   \
            }                                  \
        }                                      \
    }

#endif /* EC041CB6_6FF5_45E9_9157_0C2F01B0A805 */
