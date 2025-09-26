#ifndef F5D34A4C_A9D2_46DB_BAA7_FC7204C1A38D
#define F5D34A4C_A9D2_46DB_BAA7_FC7204C1A38D

#include <list>
#include <map>
#include <nlohmann/json.hpp>

#include "estring.h"
#include "modules/serialization/jsonserializer.h"

namespace Bot
{
    class PromptSectionList
    {
    public:
        PromptSectionList() = default;
        PromptSectionList(const EString& title, bool numbered);

        PromptSectionList& add(const EString& item);

        void clear();
        bool empty() const;

        const EString& title() const;
        bool isNumbered() const;

        std::list<EString>::const_iterator begin() const;
        std::list<EString>::const_iterator end() const;

        nlohmann::json toJson() const;
        void fromJson(const nlohmann::json& j);

    private:
        EString m_title;
        bool m_numbered{ false };
        std::list<EString> m_items;
    };

    class PromptGenerator
    {
    public:
        explicit PromptGenerator(const EString& name,
                                 const std::string& configFile,
                                 std::shared_ptr<Serialization::JsonApi> jsonApi);

        class SectionProxy
        {
        public:
            SectionProxy(PromptSectionList& section, PromptGenerator& parent);
            SectionProxy& add(const EString& item);
            operator PromptSectionList&();

        private:
            PromptSectionList& m_section;
            PromptGenerator& m_parent;
        };

        SectionProxy addSection(const EString& title, bool numbered = false);
        EString generate() const;

    private:
        void saveToJson() const;
        void loadFromJson();
        void autoSave();

        EString m_name;
        EString m_configFile;
        std::map<EString, PromptSectionList> m_sections;
        std::shared_ptr<Serialization::JsonApi> m_jsonApi;
    };

} // namespace Bot

#endif /* F5D34A4C_A9D2_46DB_BAA7_FC7204C1A38D */
