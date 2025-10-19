#include "jsonapi.h"

using namespace Serialization;

JsonApi::JsonApi(std::string path) : m_path(std::move(path)) {}

nlohmann::json JsonApi::loadJson() const
{
    std::ifstream f(m_path.c_str());
    if (!f.is_open())
    {
        return nlohmann::json::object();
    }
    nlohmann::json j;
    f >> j;
    return j;
}

void JsonApi::saveJson(const nlohmann::json& j) const
{
    ensureDirs();
    std::ofstream(m_path) << j.dump(4);
}

void JsonApi::erase(const std::string& jsonPointer) const
{
    auto j = loadJson();
    auto ptr = nlohmann::json::json_pointer(jsonPointer);
    j.erase(ptr.to_string());
    saveJson(j);
}

void JsonApi::ensureDirs() const
{
    std::filesystem::path path(m_path.c_str());
    std::filesystem::create_directories(path.parent_path());
}