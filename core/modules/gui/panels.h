#ifndef D13ED700_2880_4408_BA93_33D6DE08BB90
#define D13ED700_2880_4408_BA93_33D6DE08BB90
#include <memory>
#include <utility>
#include <vector>

#include "ipanel.h"

namespace Gui
{
    class Panels
    {
    public:
        using PanelList = std::vector<std::unique_ptr<IPanel>>;

        explicit Panels(PanelList panels) : m_panels(std::move(panels)) {}

        template <typename T>
        T* getPanel() const
        {
            for (auto& p : m_panels)
            {
                if (auto* hit = dynamic_cast<T*>(p.get()))
                {
                    return hit;
                }
            }
            return nullptr;
        }

        void onInits();

        void setVisibles();

        void onRenders();

    private:
        Panels(const Panels&) = delete;
        Panels& operator=(const Panels&) = delete;
        Panels(Panels&&) = delete;
        Panels& operator=(Panels&&) = delete;

        PanelList m_panels;
    };

} // namespace Gui

#endif /* D13ED700_2880_4408_BA93_33D6DE08BB90 */
