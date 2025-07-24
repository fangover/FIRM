#ifndef CEEA0A94_86C6_404B_88A6_FE2CC618D48F
#define CEEA0A94_86C6_404B_88A6_FE2CC618D48F

#include "core/assemblies/strategies/interface/idetector.h"

template <typename T>
class EResultValue;
struct Signal;

namespace ScalpingM1
{
    class Detector : public Strategies::IDetector
    {
    public:
        virtual ~Detector();
        virtual EResultValue<Signal> detect() const override;
    };

} // namespace ScalpingM1
#endif /* CEEA0A94_86C6_404B_88A6_FE2CC618D48F */
