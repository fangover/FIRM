#pragma once
#include "jsonapi.h"

using namespace Serialization;

template <typename T>
void JsonApi::save(const T& obj) const
{
    ensureDirs();
    nlohmann::json j = obj;
    std::ofstream(m_path) << j.dump(4);
}

template <typename V>
void JsonApi::update(const std::string& jsonPointer, const V& value) const
{
    auto j = loadJson();
    j[nlohmann::json::json_pointer(jsonPointer)] = value;
    saveJson(j);
}

template <typename V>
std::optional<V> JsonApi::get(const std::string& jsonPointer) const
{
    auto j = loadJson();
    auto ptr = nlohmann::json::json_pointer(jsonPointer);
    if (!j.contains(ptr))
    {
        return std::nullopt;
    }
    return j[ptr].get<V>();
}
