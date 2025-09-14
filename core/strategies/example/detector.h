#ifndef CEEA0A94_86C6_404B_88A6_FE2CC618D48F
#define CEEA0A94_86C6_404B_88A6_FE2CC618D48F

#include "strategies/interface/idetector.h"

template <typename T>
class EResultValue;
struct Signal;

namespace ExampleStrat
{
    class Detector : public Strategies::IDetector
    {
    public:
        virtual ~Detector();
        virtual EResultValue<Signal> detect() const override;
    };

} // namespace ExampleStrat
#endif /* CEEA0A94_86C6_404B_88A6_FE2CC618D48F */
