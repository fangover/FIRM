#include "panels.h"
#include "imgui.h"

using namespace Gui;

void Panels::onInits()
{
    for (auto& panel : m_panels)
    {
        panel->onInit();
    }
}

void Panels::setVisibles()
{
    ImGui::Begin("Panel Manager");
    for (auto& panel : m_panels)
    {
        bool visible = panel->isVisible();
        if (ImGui::Checkbox(panel->name().data(), &visible))
        {
            panel->setVisible(visible);
        }
    }
    ImGui::End();
}

void Panels::onRenders()
{
    for (auto& panel : m_panels)
    {
        if (!panel->isVisible())
        {
            continue;
        }

        ImGui::Begin(panel->name().data());
        panel->onRender();
        ImGui::End();
    }
}
