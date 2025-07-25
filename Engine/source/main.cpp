#include <basicstdlib.h>
#include <eresult.h>
#include <filestreamhandle.h>
#include <log.h>

#include "core/include/globalEnum.h"
#include "core/assemblies/strategies/interface/idetector.h"
#include "core/assemblies/strategies/ExampleStrat/include/detector.h"

int main()
{
    std::unique_ptr<Strategies::IDetector> detector = std::make_unique<ExampleStrat::Detector>();
    auto tes = detector->detect().value();
    std::cout << static_cast<int>(tes.direction) << " " << tes.reason;

    int num = 123;
    LOG(EString{}.sprintf("Int: %d", num));

    std::string text = "Hello";
    LOG(EString{}.sprintf("String: %s", toStr(text).data()));

    return 0;
}