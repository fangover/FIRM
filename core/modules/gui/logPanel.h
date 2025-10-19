#ifndef CA466480_D313_423A_A5F7_006DBEC04C2A
#define CA466480_D313_423A_A5F7_006DBEC04C2A

#include "ipanel.h"

namespace Gui
{
    class LogPanel : public IPanel
    {
    public:
        explicit LogPanel(std::string strName) : m_strName(strName) {}

        const std::string& name() const override;
        void onInit() override;
        void onRender() override;

    private:
        LogPanel(const LogPanel&) = delete;
        LogPanel& operator=(const LogPanel&) = delete;
        LogPanel(LogPanel&&) = delete;
        LogPanel& operator=(LogPanel&&) = delete;

        void clear();
        int findSelectableLevels() const;

        bool autoScroll = true;
        std::string m_strName;

        int m_nSelectedIndex;
        std::vector<Elvl> m_lstSelectableLevels;
        std::vector<std::string> m_lstLevelNames;
    };
} // namespace Gui
#endif /* CA466480_D313_423A_A5F7_006DBEC04C2A */
