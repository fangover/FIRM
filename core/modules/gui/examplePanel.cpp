#include "imgui.h"

#include "examplePanel.h"

using namespace Gui;

const std::string& ExamplePanel::name() const
{
    return m_strName;
}

void ExamplePanel::onRender()
{
    ImGui::Text("Frame time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
}
