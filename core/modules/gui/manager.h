#ifndef D299D943_91EE_4A02_B255_39A52D7C4797
#define D299D943_91EE_4A02_B255_39A52D7C4797
#pragma once

#include "ipanel.h"

namespace Gui
{
    class Manager
    {
    public:
        void initialize();
        void render();
        void shutDown();
        bool shouldClose() const;

        void addPanel(std::unique_ptr<IPanel> panel);

    private:
        std::vector<std::unique_ptr<IPanel>> m_lstPanels;
    };
} // namespace Gui

#endif /* D299D943_91EE_4A02_B255_39A52D7C4797 */
