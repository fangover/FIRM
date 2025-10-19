#ifndef F5D34A4C_A9D2_46DB_BAA7_FC7204C1A38D
#define F5D34A4C_A9D2_46DB_BAA7_FC7204C1A38D

#include <list>
#include <map>
#include <nlohmann/json.hpp>

#include "modules/serialization/jsonapi.h"

namespace Bot
{
    class PromptSectionList
    {
    public:
        PromptSectionList() = default;
        PromptSectionList(const std::string& title, bool numbered);

        PromptSectionList& add(const std::string& item);

        void clear();
        bool empty() const;

        const std::string& title() const;
        bool isNumbered() const;

        std::list<std::string>::const_iterator begin() const;
        std::list<std::string>::const_iterator end() const;

        nlohmann::json toJson() const;
        void fromJson(const nlohmann::json& j);

    private:
        std::string m_title;
        bool m_numbered{ false };
        std::list<std::string> m_items;
    };

    class PromptGenerator
    {
    public:
        explicit PromptGenerator(const std::string& name,
                                 const std::string& configFile,
                                 std::shared_ptr<Serialization::JsonApi> jsonApi);

        class SectionProxy
        {
        public:
            SectionProxy(PromptSectionList& section, PromptGenerator& parent);
            SectionProxy& add(const std::string& item);
            operator PromptSectionList&();

        private:
            PromptSectionList& m_section;
            PromptGenerator& m_parent;
        };

        SectionProxy addSection(const std::string& title, bool numbered = false);
        std::string generate() const;

    private:
        void saveToJson() const;
        void loadFromJson();
        void autoSave();

        std::string m_name;
        std::string m_configFile;
        std::map<std::string, PromptSectionList> m_sections;
        std::shared_ptr<Serialization::JsonApi> m_jsonApi;
    };

} // namespace Bot

#endif /* F5D34A4C_A9D2_46DB_BAA7_FC7204C1A38D */
