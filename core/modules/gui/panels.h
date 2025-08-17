#ifndef D13ED700_2880_4408_BA93_33D6DE08BB90
#define D13ED700_2880_4408_BA93_33D6DE08BB90
#ifndef A18D02B8_8122_4859_BAC6_913B61883A8A
#define A18D02B8_8122_4859_BAC6_913B61883A8A
#include <memory>
#include <utility>
#include <vector>
#include "ipanel.h"

class EString;
namespace Gui
{
    class Panels
    {
    public:
        using PanelList = std::vector<std::unique_ptr<IPanel>>;

        explicit Panels(PanelList panels) : m_panels(std::move(panels)) {}

        template <typename T>
        T *getPanel() const
        {
            for (auto &p : m_panels)
            {
                if (typeid(*p) == typeid(T))
                    return static_cast<T *>(p.get());
            }
            return nullptr;
        }

        void onInits();

        void setVisibles();

        void onRenders();

    private:
        PanelList m_panels;
    };

} // namespace Gui

#endif /* A18D02B8_8122_4859_BAC6_913B61883A8A */

#endif /* D13ED700_2880_4408_BA93_33D6DE08BB90 */
