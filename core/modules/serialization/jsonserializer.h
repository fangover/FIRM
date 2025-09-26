#ifndef D66BB19D_A96C_4620_832B_DE6EFDD8B21F
#define D66BB19D_A96C_4620_832B_DE6EFDD8B21F

// json_api.h
#pragma once
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

namespace Serialization
{
    class JsonApi
    {
    public:
        explicit JsonApi(std::string path) : m_path(std::move(path)) {}

        template <typename T>
        void save(const T& obj) const
        {
            ensureDirs();
            nlohmann::json j = obj;
            std::ofstream(m_path) << j.dump(4);
        }

        template <typename T>
        T load() const
        {
            std::ifstream f(m_path);
            if (!f.is_open())
            {
                return T{};
            }
            nlohmann::json j;
            f >> j;
            return j.get<T>();
        }

        nlohmann::json loadJson() const
        {
            std::ifstream f(m_path);
            if (!f.is_open())
            {
                return nlohmann::json::object();
            }
            nlohmann::json j;
            f >> j;
            return j;
        }

        void saveJson(const nlohmann::json& j) const
        {
            LOG("saved?");
            ensureDirs();
            std::ofstream(m_path) << j.dump(4);
        }

        template <typename V>
        void update(const std::string& jsonPointer, const V& value) const
        {
            auto j = loadJson();
            j[nlohmann::json::json_pointer(jsonPointer)] = value;
            saveJson(j);
        }

        template <typename V>
        std::optional<V> get(const std::string& jsonPointer) const
        {
            auto j = loadJson();
            auto ptr = nlohmann::json::json_pointer(jsonPointer);
            if (!j.contains(ptr))
            {
                return std::nullopt;
            }
            return j[ptr].get<V>();
        }

        void erase(const std::string& jsonPointer) const
        {
            auto j = loadJson();
            auto ptr = nlohmann::json::json_pointer(jsonPointer);
            j.erase(ptr.to_string());
            saveJson(j);
        }

    private:
        EString m_path;

        void ensureDirs() const
        {
            std::filesystem::path path(m_path.c_str());
            std::filesystem::create_directories(path.parent_path());
        }
    };
} // namespace Serialization

#endif /* D66BB19D_A96C_4620_832B_DE6EFDD8B21F */
