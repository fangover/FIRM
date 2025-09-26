#include <engine.h>
#include <memory>

#include "eglobal/service.h"

#include "modules/bot/prompt.h"
#include "modules/gui/manager.h"
#include "modules/serialization/jsonserializer.h"

namespace engine
{
    void Engine::initialize()
    {
        LOG("[Engine] Initialized.");

        m_pGuiManager = std::make_unique<Gui::Manager>();
        m_pGuiManager->initialize();

        std::shared_ptr<Serialization::JsonApi> jsonApi =
            EGlobal::Service::instancePtr<Serialization::JsonApi>("build/data/config.json");
        Bot::PromptGenerator gen("ChatBot", "build/data/config.json", jsonApi);
        gen.addSection("CONTEXT").add("Knows C++").add("Understands templates");
        gen.addSection("RULES", true).add("Be clear").add("Be concise");
        gen.addSection("TASKS", true).add("Answer user question");
        LOG(gen.generate());
    }

    void Engine::runLoop()
    {
        // TODO: Reform the whole managers structure.
        while (!m_pGuiManager->shouldClose())
        {
            m_pGuiManager->onRender();
        }

        m_pGuiManager->shutDown();
    }
} // namespace engine
