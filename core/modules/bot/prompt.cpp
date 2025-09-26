#include "prompt.h"
#include "log.h"

using namespace Bot;

PromptSectionList::PromptSectionList(const EString& title, bool numbered) : m_title(title), m_numbered(numbered) {}

PromptSectionList& PromptSectionList::add(const EString& item)
{
    LOG_ENTRY;

    m_items.push_back(item);
    return *this;
}

void PromptSectionList::clear()
{
    m_items.clear();
}

bool PromptSectionList::empty() const
{
    return m_items.empty();
}

const EString& PromptSectionList::title() const
{
    return m_title;
}

bool PromptSectionList::isNumbered() const
{
    return m_numbered;
}

std::list<EString>::const_iterator PromptSectionList::begin() const
{
    return m_items.begin();
}

std::list<EString>::const_iterator PromptSectionList::end() const
{
    return m_items.end();
}

nlohmann::json PromptSectionList::toJson() const
{
    LOG_ENTRY;

    return { { "name", m_title.data() },
             { "is_numbered", m_numbered },
             { "items", std::vector<std::string>(m_items.begin(), m_items.end()) } };
}

void PromptSectionList::fromJson(const nlohmann::json& j)
{
    LOG_ENTRY;

    m_title = j.value("name", m_title.c_str());
    m_numbered = j.value("is_numbered", false);
    m_items.clear();
    for (const auto& it : j["items"])
    {
        m_items.push_back(it.get<std::string>());
    }
}

PromptGenerator::SectionProxy::SectionProxy(PromptSectionList& section, PromptGenerator& parent)
    : m_section(section)
    , m_parent(parent)
{
}

PromptGenerator::SectionProxy& PromptGenerator::SectionProxy::add(const EString& item)
{
    LOG_ENTRY;
    m_section.add(item);
    m_parent.autoSave();
    return *this;
}

PromptGenerator::SectionProxy::operator PromptSectionList&()
{
    return m_section;
}

PromptGenerator::PromptGenerator(const EString& name,
                                 const std::string& configFile,
                                 std::shared_ptr<Serialization::JsonApi> jsonApi)
    : m_name(name)
    , m_configFile(configFile)
    , m_jsonApi(std::move(jsonApi))
{
    loadFromJson();
}

PromptGenerator::SectionProxy PromptGenerator::addSection(const EString& title, bool numbered)
{
    LOG_ENTRY;

    auto it = m_sections.find(title);
    if (it == m_sections.end())
    {
        it = m_sections.emplace(title, PromptSectionList(title, numbered)).first;
    }

    autoSave();
    return SectionProxy(it->second, *this);
}

EString PromptGenerator::generate() const
{
    LOG_ENTRY;

    EString genStr;
    genStr.sprintf("Your name is %s.\n\n", m_name.data());

    auto appendSection = [](EString& out, const PromptSectionList& section)
    {
        if (section.empty())
        {
            return;
        }

        out << "--- " << section.title() << " START ---\n";
        int i = 1;
        for (const auto& s : section)
        {
            EString prefix = section.isNumbered() ? toStr(i++) + ". " : "- ";
            out << prefix << s << "\n";
        }
        out << "--- " << section.title() << " END ---\n\n";
    };

    for (const auto& [title, section] : m_sections)
    {
        appendSection(genStr, section);
    }

    return genStr;
}

void PromptGenerator::loadFromJson()
{
    LOG_ENTRY;

    if (!m_jsonApi)
    {
        return;
    }

    auto j = m_jsonApi->loadJson();
    m_sections.clear();

    if (!j.contains("sections"))
    {
        return;
    }

    for (const auto& sec : j["sections"])
    {
        PromptSectionList section;
        section.fromJson(sec);
        m_sections.emplace(section.title(), section);
    }
}

void PromptGenerator::saveToJson() const
{
    LOG_ENTRY;

    if (!m_jsonApi)
    {
        return;
    }

    nlohmann::json j;
    j["sections"] = nlohmann::json::array();

    for (const auto& [title, section] : m_sections)
    {
        j["sections"].push_back(section.toJson());
    }

    m_jsonApi->saveJson(j);
}

void PromptGenerator::autoSave()
{
    LOG_ENTRY;

    if (m_jsonApi)
    {
        saveToJson();
    }
}