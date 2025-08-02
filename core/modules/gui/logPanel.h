#ifndef CA466480_D313_423A_A5F7_006DBEC04C2A
#define CA466480_D313_423A_A5F7_006DBEC04C2A

#include "ipanel.h"

namespace Gui
{
    class LogPanel : public IPanel
    {
    public:
        explicit LogPanel(EString strName) : m_strName(strName) {}

        const EString &name() const override;
        void onRender() override;

    private:
        void clear();

        bool autoScroll = true;
        EString m_strName;
    };
} // namespace Gui
#endif /* CA466480_D313_423A_A5F7_006DBEC04C2A */
