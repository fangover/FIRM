#include <basicstdlib.h>
#include <eresult.h>
#include <filestreamhandle.h>

#include "core/include/globalEnum.h"
#include "core/assemblies/strategies/interface/idetector.h"
#include "core/assemblies/strategies/scalpingm1/include/detector.h"

int main()
{
    std::unique_ptr<Strategies::IDetector> detector = std::make_unique<ScalpingM1::Detector>();
    auto tes = detector->detect().value();
    std::cout << static_cast<int>(tes.direction) << " " << tes.reason;

    return 0;
}