#ifndef D66BB19D_A96C_4620_832B_DE6EFDD8B21F
#define D66BB19D_A96C_4620_832B_DE6EFDD8B21F

#include <nlohmann/json.hpp>

namespace Serialization
{
    class JsonApi
    {
    public:
        explicit JsonApi(std::string path);

        nlohmann::json loadJson() const;
        void saveJson(const nlohmann::json& j) const;

        template <typename T>
        void save(const T& obj) const;
        template <typename V>
        void update(const std::string& jsonPointer, const V& value) const;
        template <typename V>
        std::optional<V> get(const std::string& jsonPointer) const;

        void erase(const std::string& jsonPointer) const;

    private:
        std::string m_path;

        void ensureDirs() const;
    };
} // namespace Serialization

#include "jsonapi.tpp"

#endif /* D66BB19D_A96C_4620_832B_DE6EFDD8B21F */
