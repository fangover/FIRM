#include "logPanel.h"

#include "imgui.h"

using namespace Gui;

const std::string& LogPanel::name() const
{
    return m_strName;
}

void LogPanel::onInit()
{
    m_lstSelectableLevels = { Elvl::eAlways, Elvl::eInfo, Elvl::eSummary, Elvl::eDetails, Elvl::eDebug, Elvl::eFull };
    m_nSelectedIndex = findSelectableLevels();

    for (Elvl elevel : m_lstSelectableLevels)
    {
        m_lstLevelNames.push_back(toUser(elevel));
    }
}

void LogPanel::onRender()
{
    LOG_ENTRY;

    auto lstRecentLogs = Logger::getRecentLogs();
    m_nSelectedIndex = findSelectableLevels();

    // Setup.
    if (ImGui::Button("Clear"))
    {
        clear();
    }
    ImGui::SameLine();
    ImGui::Checkbox("Auto-scroll", &autoScroll);
    ImGui::SameLine();
    ImGui::Text("Log Level:");
    ImGui::SameLine();

    std::vector<const char*> tempLevelNames;
    for (const auto& s : m_lstLevelNames)
    {
        tempLevelNames.push_back(s.c_str());
    }

    if (ImGui::Combo("##logLevel", &m_nSelectedIndex, tempLevelNames.data(), static_cast<int>(tempLevelNames.size())))
    {
        Logger::setCurrentLogLevel(static_cast<Elvl>(m_nSelectedIndex));
    }

    // Log output
    ImGui::Separator();
    ImGui::BeginChild("LogRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

    for (const auto& line : lstRecentLogs)
    {
        ImGui::TextUnformatted(line.data());
    }

    if (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    {
        ImGui::SetScrollHereY(1.0f);
    }

    ImGui::EndChild();
}

void LogPanel::clear()
{
    Logger::clearRecentLogs();
}

int LogPanel::findSelectableLevels() const
{
    auto idx = std::ranges::find(m_lstSelectableLevels, Logger::getCurrentLogLevel()) - m_lstSelectableLevels.begin();
    return static_cast<int>(idx);
}
