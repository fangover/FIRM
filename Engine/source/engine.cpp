#include <engine/engine.h>
#include <core/include/globalEnum.h>
#include <core/strategies/examplestrat/include/detector.h>

namespace engine
{
    void Engine::initialize()
    {
        std::cout << "[Engine] Initialized.\n";
    }

    void Engine::runLoop()
    {

        std::unique_ptr<Strategies::IDetector> detector = std::make_unique<ExampleStrat::Detector>();
        auto tes = detector->detect().value();
        LOG("Direction: %d , Reason: %s", static_cast<int>(tes.direction), tes.reason.data());

        int num = 123;
        LOG(EString{}.sprintf("Int: %d", num));

        std::string text = "Hello";
        LOG(EString{}.sprintf("String: %s", toStr(text).data()));

        std::cout << "[Engine] Running main loop...\n";
        // Basic loop (stub)
        for (int i = 0; i < 3; ++i)
            std::cout << "Tick " << i << '\n';
    }
}
