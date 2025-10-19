#include <curl/curl.h>
#include <engine.h>
#include <memory>

#include "eglobal/service.h"
#include "estring.h"
#include "filestreamhandle.h"

#include "fcpath.h"
#include "logger.h"
#include "modules/bot/prompt.h"
#include "modules/chatgpt/client.h"
#include "modules/gui/manager.h"
#include "modules/serialization/jsonapi.h"

namespace engine
{
    void Engine::initialize()
    {
        LOG("[Engine] Initialized.");

        m_guiManager = std::make_unique<Gui::Manager>();
        m_guiManager->initialize();

        m_threadManager.add<ChatThread>(
            [this](std::stop_token stoken)
            {
                auto jsonApi = EGlobal::Service::instancePtr<Serialization::JsonApi>(Paths::Config + "config.json");
                Bot::PromptGenerator gen("ChatBot", "build/data/config.json", jsonApi);
                gen.addSection("CONTEXT").add("Knows C++").add("Understands templates");
                gen.addSection("RULES", true).add("Be clear").add("Be concise");
                gen.addSection("TASKS", true).add("Answer user question");
                auto promptText = (gen.generate());

                auto chatgptAIApi = FileStream::FileHandle(Paths::Config + "chatgptai.txt");
                std::string chatgptAPI;
                chatgptAIApi.getContent(chatgptAPI);

                ChatGPTAI::Client client(chatgptAPI);

                constexpr int promptIntervalSeconds = 10;
                int secondsElapsed = 0;

                while (!stoken.stop_requested() && m_running)
                {
                    // TODO: temp prompt
                    if (secondsElapsed >= promptIntervalSeconds)
                    {
                        try
                        {
                            auto resp = client.chat(promptText);
                            promptText = "what did I asked you earlier?";
                            if (resp.value().error.has_value())
                            {
                                LOG_ERROR(EString::sprintf("Provider error: %s", *resp.value().error));
                            }
                            LOG("Model: " + resp.value().model);
                            if (!resp.value().output.empty() && !resp.value().output[0].content.empty())
                            {
                                LOG("Text: " + resp.value().output[0].content[0].text);
                            }
                            else
                            {
                                LOG("No content in response");
                            }
                        }
                        catch (const std::exception& e)
                        {
                            LOG_LEVEL(Elvl::eError, EString::sprintf("ChatGPT Thread Error : %s") + e.what());
                        }
                        secondsElapsed = 0;
                    }

                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    secondsElapsed++;
                }

                client.resetMemory();
            });

        m_threadManager.startAll();
    }

    void Engine::runLoop()
    {
        // TODO: Reform the whole managers structure.
        LOG("[Engine] Entering main render loop...");

        while (!m_guiManager->shouldClose())
        {
            m_guiManager->onRender();
        }
        LOG("[Engine] GUI closed, shutting down...");

        m_running = false;
        m_threadManager.stopAll();
        m_threadManager.joinAll();

        m_guiManager->shutDown();
        LOG("[Engine] Shutdown complete.");
    }
} // namespace engine
