#ifndef D299D943_91EE_4A02_B255_39A52D7C4797
#define D299D943_91EE_4A02_B255_39A52D7C4797

#include "panels.h"
namespace Gui
{
    class Manager
    {
    public:
        Manager();

        void initialize();
        void onRender();
        void shutDown();
        bool shouldClose() const;

    private:
        // Panels m_lstPanels;
        Panels m_panels;
    };
} // namespace Gui

#endif /* D299D943_91EE_4A02_B255_39A52D7C4797 */
