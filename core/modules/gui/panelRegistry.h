#ifndef B4E586A6_6162_4DEA_BD7C_A9FF10DEDE2B
#define B4E586A6_6162_4DEA_BD7C_A9FF10DEDE2B

#include "iPanel.h"
#include "examplePanel.h"
#include "logPanel.h"

namespace Gui
{
    class PanelRegistry
    {
    public:
        static std::vector<std::unique_ptr<IPanel>> getDefaultPanels()
        {
            std::vector<std::unique_ptr<IPanel>> panels;
            panels.push_back(std::make_unique<ExamplePanel>("ExamplePanel"));
            panels.push_back(std::make_unique<LogPanel>("LogPanel"));
            // Add more here
            return panels;
        }
    };

} // namespace Gui

#endif /* B4E586A6_6162_4DEA_BD7C_A9FF10DEDE2B */
