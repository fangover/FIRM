#include <engine/Engine.h>
#include <launcher.h>

namespace app
{
    void Launcher::run()
    {
        engine::Engine engine;
        engine.initialize();
        engine.runLoop();
    }
} // namespace app
