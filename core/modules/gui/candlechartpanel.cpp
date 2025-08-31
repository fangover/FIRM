#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "candlechartpanel.h"
#include "common/candle.h"

using namespace Gui;

const EString &CandleChartPanel::name() const
{
    return m_strName;
}

void CandleChartPanel::onRender()
{
    Candle candle = candle.open(15.0);
    candle.open(15.0).close(100.0).volume(100.0);

    LOG(EString{}.sprintf("caneld %s", toStr(candle.open()).data()));
}
