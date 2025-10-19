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
        ThreadManager m_threadManager;
        std::unique_ptr<Gui::Manager> m_guiManager;
        std::atomic<bool> m_running{ true };
    };
} // namespace engine

#endif /* B9ECA8CE_8322_436E_B0E8_8D9A7BA07A14 */
