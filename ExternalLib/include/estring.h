#ifndef EC041CB6_6FF5_45E9_9157_0C2F01B0A805
#define EC041CB6_6FF5_45E9_9157_0C2F01B0A805
#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>
#include <utility>
#include <vector>
#include <regex>

namespace
{
    std::string simple_format(const std::string &fmt, const std::vector<std::string> &args)
    {
        std::string result = fmt;
        for (const auto &arg : args)
        {
            result = std::regex_replace(result, std::regex("\\{\\}"), arg, std::regex_constants::format_first_only);
        }
        return result;
    }
}

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
std::enable_if_t<std::is_enum_v<T> && has_toUser_v<T>, std::string>
toStr(T value)
{
    return toUser(value);
}

class EString
{
    std::string value;

public:
    EString() = default;
    EString(std::string str) : value(std::move(str)) {}

    template <typename... Args>
    EString &sprintf(const std::string &fmt, Args &&...args)
    {
        std::vector<std::string> strArgs = {toStr(std::forward<Args>(args))...};
        value = simple_format(fmt, strArgs);
        return *this;
    }

    operator const std::string &() const { return value; }
    const char *data() const { return value.data(); }
};

#endif /* EC041CB6_6FF5_45E9_9157_0C2F01B0A805 */
