#include <app/Launcher.h>
#include <engine/Engine.h>

namespace app
{
    void Launcher::run()
    {
        engine::Engine engine;
        engine.initialize();
        engine.runLoop();
    }
}
