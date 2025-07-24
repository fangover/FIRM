#ifndef D0003EEB_98A9_4224_8B3E_359E7A654C4A
#define D0003EEB_98A9_4224_8B3E_359E7A654C4A

#include <chrono>
#include <iostream>
#include <iomanip>

using eTimeStamp = std::chrono::system_clock::time_point;
using eClock = std::chrono::system_clock;

struct Candle
{
    eTimeStamp time;
    double open;
    double close;
    double high;
    double low;
    double volume;

    Candle(eTimeStamp t, double o, double c, double h, double l, double v)
        : time(t), open(o), close(c), high(h), low(l), volume(v) {}

    bool operator<(const Candle &other) const
    {
        return time < other.time;
    }
};

#endif /* D0003EEB_98A9_4224_8B3E_359E7A654C4A */
