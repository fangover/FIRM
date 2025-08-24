#ifndef C7533AFB_58DD_4D5E_9BDC_C169B8584C39
#define C7533AFB_58DD_4D5E_9BDC_C169B8584C39
#include <string>

enum class Direction
{
    None = 0,
    Buy = 1,
    Sell = -1
};

struct Signal
{
    Direction direction;
    std::string reason;
};

enum class Timeframe
{
    M1,
    M5,
    M15,
    H1,
    D1
};

#endif /* C7533AFB_58DD_4D5E_9BDC_C169B8584C39 */
