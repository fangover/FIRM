#ifndef AA95CFCD_2FE6_43C6_ACF7_D2FA2D812025
#define AA95CFCD_2FE6_43C6_ACF7_D2FA2D812025
#include <chrono>
#include "globalEnum.h"

using Timestamp = std::chrono::utc_time<std::chrono::milliseconds>;

constexpr std::chrono::minutes tf_duration(Timeframe tf)
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

namespace
{
    template <class Dur>
    [[nodiscard]] inline Timestamp floorTimeFrame(std::chrono::utc_time<Dur> t, Timeframe tf)
    {
        using namespace std::chrono;
        const auto d = tf_duration(tf);
        const auto sys = clock_cast<system_clock>(t);
        const auto floored = time_point_cast<minutes>(sys).time_since_epoch() / d * d;
        return clock_cast<utc_clock>(sys_time<minutes>{floored});
    }
}

struct Candle
{
    Timestamp ts;
    double m_open{};
    double m_high{};
    double m_low{};
    double m_close{};
    double m_volume{};
    Timeframe m_timeFrame{Timeframe::M1};

    Candle() = default;
    Candle(Timestamp timestamp_utc,
           double o, double h, double l, double c,
           double v, Timeframe timeframe)
        : ts(floorTimeFrame(timestamp_utc, timeframe)),
          m_open(o), m_high(h), m_low(l), m_close(c), m_volume(v), m_timeFrame(timeframe)
    {
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
};

#endif /* AA95CFCD_2FE6_43C6_ACF7_D2FA2D812025 */
