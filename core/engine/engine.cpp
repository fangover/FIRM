#include <engine.h>

#include <eglobalregistry.h>

#include <common/globalEnum.h>
#include <modules/gui/manager.h>
#include <strategies/example/detector.h>

#include "modules/gui/panelRegistry.h"

namespace engine
{
    void Engine::initialize()
    {
        LOG("[Engine] Initialized.");

        m_pGuiManager = std::make_unique<Gui::Manager>();
    }

    void Engine::runLoop()
    {
        m_pGuiManager->initialize();

        auto lastActionTime = std::chrono::steady_clock::now();

        while (!m_pGuiManager->shouldClose())
        {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastActionTime);
            if (elapsed.count() >= 5)
            {
                LOG_LEVEL(Elvl::eDebug, "test");
                lastActionTime = now;
            }
            m_pGuiManager->onRender();
        }
        m_pGuiManager->shutDown();
    }
} // namespace engine
