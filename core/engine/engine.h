#ifndef B9ECA8CE_8322_436E_B0E8_8D9A7BA07A14
#define B9ECA8CE_8322_436E_B0E8_8D9A7BA07A14
#include <modules/gui/manager.h>

namespace engine
{
    class Engine
    {
    public:
        void initialize();
        void runLoop();

        std::unique_ptr<Gui::Manager> m_pGuiManager;
    };
}

#endif /* B9ECA8CE_8322_436E_B0E8_8D9A7BA07A14 */
