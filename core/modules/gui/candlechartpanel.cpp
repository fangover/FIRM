#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "candlechartpanel.h"

using namespace Gui;

const EString& CandleChartPanel::name() const
{
    return m_strName;
}

void CandleChartPanel::onRender() {}
