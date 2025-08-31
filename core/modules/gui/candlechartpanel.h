#ifndef BAD9F0BF_7264_4D33_83DD_EB18437CB673
#define BAD9F0BF_7264_4D33_83DD_EB18437CB673
#include "iPanel.h"
#include "estring.h"
#include "candles.h"

namespace Gui
{

    class CandleChartPanel : public IPanel
    {
    public:
        explicit CandleChartPanel(EString strName) : m_strName(strName) {}

        const EString &name() const override;
        void onInit() override {};
        void onRender() override;

    private:
        EString m_strName;
    };

} // namespace Gui

#endif /* BAD9F0BF_7264_4D33_83DD_EB18437CB673 */
