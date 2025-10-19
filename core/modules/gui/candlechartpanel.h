#ifndef BAD9F0BF_7264_4D33_83DD_EB18437CB673
#define BAD9F0BF_7264_4D33_83DD_EB18437CB673
#include "ipanel.h"

namespace Gui
{
    class CandleChartPanel : public IPanel
    {
    public:
        explicit CandleChartPanel(std::string strName) : m_strName(strName) {}

        const std::string& name() const override;
        void onInit() override {};
        void onRender() override;

    private:
        std::string m_strName;
    };

} // namespace Gui

#endif /* BAD9F0BF_7264_4D33_83DD_EB18437CB673 */
