#ifndef BA37726D_63B5_49AF_86D0_044DA1F29C3F
#define BA37726D_63B5_49AF_86D0_044DA1F29C3F

#include "ipanel.h"

namespace Gui
{
    class ExamplePanel : public IPanel
    {
    public:
        explicit ExamplePanel(std::string strName) : m_strName(strName) {}

        const std::string& name() const override;
        void onInit() override {};
        void onRender() override;

    private:
        std::string m_strName;
    };

} // namespace Gui

#endif /* BA37726D_63B5_49AF_86D0_044DA1F29C3F */
