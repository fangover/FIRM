#ifndef B9ECA8CE_8322_436E_B0E8_8D9A7BA07A14
#define B9ECA8CE_8322_436E_B0E8_8D9A7BA07A14

#include "threadmanager.h"

#include "modules/gui/manager.h"

namespace engine
{
    struct ChatThread
    {
    };
    class Engine
    {
    public:
        void initialize();
        void runLoop();

    private:
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
        Engine(Engine&&) = delete;
        Engine& operator=(Engine&&) = delete;

        ThreadManager m_threadManager;
        std::unique_ptr<Gui::Manager> m_guiManager;
        std::atomic<bool> m_running{ true };
    };
} // namespace engine

#endif /* B9ECA8CE_8322_436E_B0E8_8D9A7BA07A14 */
