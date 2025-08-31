#ifndef BC86F7D2_54C8_4032_BFBC_1859356A347F
#define BC86F7D2_54C8_4032_BFBC_1859356A347F

#include "globalEnum.h"

using Timestamp = std::chrono::utc_time<std::chrono::milliseconds>;

namespace tf
{
    [[nodiscard]] constexpr std::chrono::minutes to_duration(Timeframe tf)
    {
        using namespace std::chrono;
        switch (tf)
        {
        case Timeframe::M1:
            return 1min;
        case Timeframe::M5:
            return 5min;
        case Timeframe::M15:
            return 15min;
        case Timeframe::H1:
            return 60min;
        case Timeframe::H4:
            return 240min;
        case Timeframe::D1:
            return 1440min;
        }
        return 1min; // impossible to reach
    }

    template <class Rep, class Period, class Clock, class Dur>
    constexpr std::chrono::time_point<Clock, Dur>
    floor_to(std::chrono::duration<Rep, Period> step,
             std::chrono::time_point<Clock, Dur> tp) noexcept
    {
        auto step_cast = std::chrono::duration_cast<Dur>(step);
        if (step_cast <= Dur::zero())
            return tp;

        auto t = tp.time_since_epoch();
        auto floored = (t / step_cast) * step_cast;
        return std::chrono::time_point<Clock, Dur>{floored};
    }

    template <class Clock, class Dur>
    constexpr std::chrono::time_point<Clock, Dur>
    floor_to(Timeframe tfv,
             std::chrono::time_point<Clock, Dur> tp) noexcept(noexcept(tf::floor_to(tf::to_duration(tfv), tp)))
    {
        return tf::floor_to(tf::to_duration(tfv), tp);
    }

}

class Candle
{

    void floor_now() noexcept(noexcept(tf::floor_to(m_timeFrame, m_timeStamp)))
    {
        m_timeStamp = tf::floor_to(m_timeFrame, m_timeStamp);
    }

public:
    Candle() = default;

    double open() noexcept
    {
        return m_open;
    }

    double high() noexcept
    {
        return m_high;
    }

    double low() noexcept
    {
        return m_low;
    }

    double close() noexcept
    {
        return m_close;
    }

    double volume() noexcept
    {
        return m_volume;
    }

    Timeframe TimeFrame() noexcept
    {
        return m_timeFrame;
    }

    Timestamp TimeStamp() noexcept
    {
        return m_timeStamp;
    }

    template <class Self>
    Self &&open(this Self &&self, double v) noexcept
    {
        self.m_open = v;
        return std::forward<Self>(self);
    }
    template <class Self>
    Self &&high(this Self &&self, double v) noexcept
    {
        self.m_high = v;
        return std::forward<Self>(self);
    }
    template <class Self>
    Self &&low(this Self &&self, double v) noexcept
    {
        self.m_low = v;
        return std::forward<Self>(self);
    }
    template <class Self>
    Self &&close(this Self &&self, double v) noexcept
    {
        self.m_close = v;
        return std::forward<Self>(self);
    }
    template <class Self>
    Self &&volume(this Self &&self, double v) noexcept
    {
        self.m_volume = v;
        return std::forward<Self>(self);
    }
    template <class Self>
    Self &&timeframe(this Self &&self, Timeframe tf_) noexcept(noexcept(tf::floor_to(tf_, self.m_timeStamp)))
    {
        self.m_timeFrame = tf_;
        self.floor_now();
        return std::forward<Self>(self);
    }

    template <class Self>
    Self &&timestamp(this Self &&self, Timestamp t_utc) noexcept(noexcept(tf::floor_to(self.m_timeFrame, t_utc)))
    {
        self.m_timeStamp = tf::floor_to(self.m_timeFrame, t_utc);
        return std::forward<Self>(self);
    }

    // TODO Move this to helper class or find a better way to clean this up
    [[nodiscard]] constexpr double body() const noexcept { return std::abs(m_close - m_open); }
    [[nodiscard]] constexpr double range() const noexcept { return m_high - m_low; }
    [[nodiscard]] constexpr bool isBullish() const noexcept { return m_close > m_open; }
    [[nodiscard]] constexpr bool isBearish() const noexcept { return m_close < m_open; }

    [[nodiscard]] constexpr double upperWick() const noexcept
    {
        return m_high - std::max(m_open, m_close);
    }

    [[nodiscard]] constexpr double lowerWick() const noexcept
    {
        return std::min(m_open, m_close) - m_low;
    }

    [[nodiscard]] constexpr double mid() const noexcept
    {
        return (m_open + m_close) * 0.5;
    }

    [[nodiscard]] constexpr double pctChange() const noexcept
    {
        return m_open != 0.0 ? (m_close - m_open) / m_open : 0.0;
    }

    [[nodiscard]] constexpr bool is_doji(double eps = 1e-9) const noexcept
    {
        return body() <= eps;
    }

    [[nodiscard]] constexpr bool contains(const Candle &other) const noexcept
    {
        return m_low <= other.m_low && m_high >= other.m_high;
    }

private:
    double m_open{};
    double m_high{};
    double m_low{};
    double m_close{};
    double m_volume{};
    Timeframe m_timeFrame{};
    Timestamp m_timeStamp{};
};

#endif /* BC86F7D2_54C8_4032_BFBC_1859356A347F */
