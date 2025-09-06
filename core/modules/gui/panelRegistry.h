#ifndef B4E586A6_6162_4DEA_BD7C_A9FF10DEDE2B
#define B4E586A6_6162_4DEA_BD7C_A9FF10DEDE2B

#include "examplePanel.h"
#include "logPanel.h"
#include "panels.h"

namespace Gui
{
    class PanelRegistry
    {
    public:
        static Panels::PanelList getDefaultPanels()
        {
            Panels::PanelList panels;
            panels.emplace_back(std::make_unique<ExamplePanel>("ExamplePanel"));
            panels.emplace_back(std::make_unique<LogPanel>("LogPanel"));
            // Add more here
            return panels;
        }
    };

} // namespace Gui

#endif /* B4E586A6_6162_4DEA_BD7C_A9FF10DEDE2B */
