#ifndef CA466480_D313_423A_A5F7_006DBEC04C2A
#define CA466480_D313_423A_A5F7_006DBEC04C2A

#include "ipanel.h"
#include <deque>
#include <string>

class LogPanel : public IPanel
{
public:
    LogPanel();

    void OnImGuiRender() override;
    void AddLog(const EString &message);
    void Clear();

private:
    std::deque<EString> logs;
    bool autoScroll = true;
};

#endif /* CA466480_D313_423A_A5F7_006DBEC04C2A */
