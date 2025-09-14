#ifndef FD1924ED_E394_44AD_B55A_22B433380EE7
#define FD1924ED_E394_44AD_B55A_22B433380EE7

class EString;
namespace Gui
{
    class IPanel
    {
    public:
        virtual ~IPanel() = default;

        virtual const EString& name() const = 0;
        virtual bool isVisible() const { return m_visible; }
        virtual void setVisible(bool v) { m_visible = v; }

        virtual void onInit() = 0;
        virtual void onRender() = 0;

    protected:
        bool m_visible = true;
    };

} // namespace Gui

#endif /* FD1924ED_E394_44AD_B55A_22B433380EE7 */
