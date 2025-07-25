#ifndef EC041CB6_6FF5_45E9_9157_0C2F01B0A805
#define EC041CB6_6FF5_45E9_9157_0C2F01B0A805
#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>
#include <utility>
#include <vector>
#include <regex>

template <typename T>
constexpr bool has_toUser_v = requires(T v) {
    { toUser(v) } -> std::convertible_to<std::string>;
};

template <typename T>
auto toStr(const T &value) -> decltype(std::ostringstream{} << value, std::string{})
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

template <typename T>
constexpr auto toCStr(const T &v) -> decltype(v.c_str())
{
    return v.c_str();
}

template <typename T>
std::enable_if_t<std::is_enum_v<T> && has_toUser_v<T>, std::string> toStr(T value)
{
    return toUser(value);
}

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

    template <typename... Args>
    EString &sprintf(const std::string &fmt, Args &&...args)
    {
        m_value = format(fmt, std::forward<Args>(args)...);
        return *this;
    }

    inline operator const std::string &() const { return m_value; }
    inline operator std::string_view() const { return m_value; }
    const char *data() const { return m_value.data(); }
};

#endif /* EC041CB6_6FF5_45E9_9157_0C2F01B0A805 */
