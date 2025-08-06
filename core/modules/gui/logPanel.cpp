#include "logPanel.h"
#include <imgui.h>

using namespace Gui;
// namespace
// {
//     inline const char *toUser(Elvl level)
//     {
//         switch (level)
//         {
//         case Elvl::eError:
//             return "ERROR";
//         case Elvl::eWarn:
//             return "WARN";
//         case Elvl::eAlways:
//             return "LOG";
//         case Elvl::eInfo:
//             return "INFO";
//         case Elvl::eSummary:
//             return "SUMMARY";
//         case Elvl::eDetails:
//             return "DETAILS";
//         case Elvl::eDebug:
//             return "DEBUG";
//         case Elvl::eFull:
//             return "FULL";
//         default:
//             return "UNKNOWN";
//         }
//     }
// }
const EString &LogPanel::name() const
{
    return m_strName;
}

void LogPanel::onRender()
{
    LOG_ENTRY;

    static const std::vector<Elvl> selectableLevels = {
        Elvl::eAlways, Elvl::eInfo, Elvl::eSummary, Elvl::eDetails, Elvl::eDebug, Elvl::eFull};
    static int selectedIndex = static_cast<int>(std::distance(
        selectableLevels.begin(),
        std::find(selectableLevels.begin(), selectableLevels.end(), Logger::getCurrentLogLevel())));

    auto lstRecentLogs = Logger::getRecentLogs();

    if (ImGui::Button("Clear"))
        clear();
    ImGui::SameLine();
    ImGui::Checkbox("Auto-scroll", &autoScroll);
    ImGui::SameLine();
    ImGui::Text("Log Level:");
    ImGui::SameLine();

    std::vector<const char *> levelNames;
    for (Elvl elevel : selectableLevels)
    {
        auto sv = toUser(elevel);
        levelNames.push_back(sv.c_str());
        LOG(EString().sprintf("Raw Elvl int value %d  << \n", static_cast<int>(elevel)));
        LOG(EString().sprintf("String %s  << \n", toUser(elevel).data()));
    }
    if (ImGui::Combo("##logLevel", &selectedIndex, levelNames.data(), static_cast<int>(levelNames.size())))
    {
        Logger::setCurrentLogLevel(static_cast<Elvl>(selectedIndex));
    }

    ImGui::Separator();
    ImGui::BeginChild("LogRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

    for (const auto &line : lstRecentLogs)
    {
        ImGui::TextUnformatted(line.data());
    }

    if (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();
}

void LogPanel::clear()
{
    Logger::clearRecentLogs();
}
