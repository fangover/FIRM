#include <engine.h>

#include <eglobalregistry.h>

#include <modules/gui/manager.h>
#include <common/globalEnum.h>
#include <strategies/example/detector.h>

#include "modules/gui/panelRegistry.h"

namespace engine
{
    void Engine::initialize()
    {
        LOG("[Engine] Initialized.");

        m_pGuiManager = std::make_unique<Gui::Manager>();

        for (auto &panel : Gui::PanelRegistry::getDefaultPanels())
        {
            m_pGuiManager->addPanel(std::move(panel));
        }
    }

    void Engine::runLoop()
    {
        m_pGuiManager->initialize();

        while (!m_pGuiManager->shouldClose())
        {
            m_pGuiManager->render();
        }
        m_pGuiManager->shutDown();
    }
}
