#include <filestreamhandle.h>
#include <eresult.h>

#include "globalEnum.h"
#include "basicstdlib.h"

#include "core/assemblies/strategies/base/interface/idetector.h"
#include "core/assemblies/strategies/scalpingm1/include/detector.h"

int main()
{
    std::unique_ptr<Strategies::IDetector> detector = std::make_unique<ScalpingM1::Dectector>();
    auto tes = detector->detect().value();
    std::cout << static_cast<int>(tes.direction) << " " << tes.reason;

    return 0;
}