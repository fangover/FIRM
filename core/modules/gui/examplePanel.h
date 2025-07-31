#ifndef BA37726D_63B5_49AF_86D0_044DA1F29C3F
#define BA37726D_63B5_49AF_86D0_044DA1F29C3F

#include "iPanel.h"

class EString;
namespace Gui
{

    class ExamplePanel : public IPanel
    {
    public:
        explicit ExamplePanel(EString strName) : m_strName(strName) {}

        const EString &name() const override;
        void render() override;

    private:
        EString m_strName;
    };

} // namespace Gui

#endif /* BA37726D_63B5_49AF_86D0_044DA1F29C3F */
