#ifndef CEEA0A94_86C6_404B_88A6_FE2CC618D48F
#define CEEA0A94_86C6_404B_88A6_FE2CC618D48F
#include <basicstdlib.h>
#include <eresultvalue.h>
#include <globalEnum.h>
#include "../../base/interface/idetector.h"

namespace ScalpingM1
{
    class Dectector : public Strategies::IDetector
    {
    public:
        Dectector() {}
        ~Dectector() {}
        EResultValue<Signal> detect() const override
        {
            LOG_ENTRY;

            Signal signal;
            signal.direction = Direction::Buy;
            signal.reason = "Nani";
            return EResultValue<Signal>::ok(signal);
        };
    };

} // namespace ScalpingM1
#endif /* CEEA0A94_86C6_404B_88A6_FE2CC618D48F */
