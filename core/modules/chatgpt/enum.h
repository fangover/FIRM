#ifndef D3A305C5_95A2_4843_8E30_F8412DB7E44E
#define D3A305C5_95A2_4843_8E30_F8412DB7E44E

#include <nlohmann/json.hpp>

namespace ChatGPTAI
{
    struct User
    {
        std::string api;
    };

    enum class Model
    {
        GPT4o_Mini,
        GPT4o
    };

    inline std::string to_string(Model m)
    {
        switch (m)
        {
            case Model::GPT4o_Mini: return "gpt-4o-mini";
            case Model::GPT4o: return "gpt-4o";
        }
        return "unknown"; // safety
    }

    struct Usage
    {
        int input_tokens = 0;
        int output_tokens = 0;
        int total_tokens = 0;
    };

    struct OutputText
    {
        std::string type;
        std::string text;
    };

    struct Message
    {
        std::string id;
        std::string type;
        std::string status;
        std::string role;
        std::vector<OutputText> content;
    };

    struct Billing
    {
        std::string payer;
    };

    struct Response
    {
        std::string id;
        std::string object;
        long created_at = 0;
        std::string status;
        bool background = false;
        Billing billing;
        std::vector<Message> output;
        std::string model;
        Usage usage;
        std::optional<std::string> error;
    };

    class ResponseProvider
    {
    public:
        explicit ResponseProvider(Response dto) : m_data(std::move(dto)) {}

        std::string_view model() const noexcept { return m_data.model; }
        bool ok() const noexcept { return !m_data.error.has_value(); }

        std::string text_summary() const
        {
            if (auto t = first_text())
            {
                return std::string(*t);
            }
            return "No content";
        }

    private:
        ResponseProvider(const ResponseProvider&) = delete;
        ResponseProvider& operator=(const ResponseProvider&) = delete;
        ResponseProvider(ResponseProvider&&) = delete;
        ResponseProvider& operator=(ResponseProvider&&) = delete;

        std::optional<std::string_view> first_text() const
        {
            for (const auto& msg : m_data.output)
            {
                for (const auto& part : msg.content)
                {
                    if (!part.text.empty())
                    {
                        return part.text;
                    }
                }
            }
            return std::nullopt;
        }

        Response m_data;
    };

} // namespace ChatGPTAI

#endif /* D3A305C5_95A2_4843_8E30_F8412DB7E44E */
