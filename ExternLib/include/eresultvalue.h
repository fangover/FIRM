#ifndef AB6B8962_3710_4702_8626_B0EAC1FAAEF6
#define AB6B8962_3710_4702_8626_B0EAC1FAAEF6

#include <cassert>
#include <string>

template <typename T>
class EResultValue
{
public:
    ~EResultValue()
    {
        (m_isOk) ? m_value.~T() : m_strError.~basic_string();
    }

    EResultValue(EResultValue &&other) noexcept
        : m_isOk(other.m_isOk)
    {
        if (m_isOk)
            new (&m_value) T(std::move(other.m_value));
        else
            new (&m_strError) std::string(std::move(other.m_strError));
    }

    EResultValue &operator=(EResultValue &&other) noexcept
    {
        if (this != &other)
        {
            if (m_isOk)
                m_value.~T();
            else
                m_strError.~basic_string();

            m_isOk = other.m_isOk;
            if (m_isOk)
                new (&m_value) T(std::move(other.m_value));
            else
                new (&m_strError) std::string(std::move(other.m_strError));
        }
        return *this;
    }

    static EResultValue<T> ok(const T &rValue)
    {
        EResultValue<T> result;
        result.m_isOk = true;
        new (&result.m_value) T(rValue);
        return result;
    }

    static EResultValue<T> ok(T &&rrValue)
    {
        EResultValue<T> result;
        result.m_isOk = true;
        new (&result.m_value) T(std::move(rrValue));
        return result;
    }

    static EResultValue<T> fail(const std::string &cstrError)
    {
        EResultValue<T> result;
        result.m_isOk = false;
        new (&result.m_strError) std::string(cstrError);
        return result;
    }

    bool isOk() const { return m_isOk; }
    bool isFail() const { return !m_isOk; }

    const T &value() const
    {
        assert(m_isOk && "Tried to access value from a failed result");
        return m_value;
    }

    const char *error() const
    {
        assert(!m_isOk && "Tried to access error from a successful result");
        return m_strError.c_str();
    }

    EResultValue(const EResultValue &) = delete;
    EResultValue &operator=(const EResultValue &) = delete;

private:
    EResultValue() : m_isOk(false) {}

    union
    {
        T m_value;
        std::string m_strError;
    };
    bool m_isOk;
};

#endif /* AB6B8962_3710_4702_8626_B0EAC1FAAEF6 */
