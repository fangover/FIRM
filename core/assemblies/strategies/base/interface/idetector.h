#ifndef BD35CEC6_8917_4CE3_AB79_AFB667881D7F
#define BD35CEC6_8917_4CE3_AB79_AFB667881D7F

#include <eresultvalue.h>
#include <string>

struct Signal;

namespace Strategies
{
    class IDetector
    {
    public:
        IDetector() {}
        ~IDetector() {}
        virtual EResultValue<Signal> detect() const = 0;
    };
} // namespace Strategies

#endif /* BD35CEC6_8917_4CE3_AB79_AFB667881D7F */
