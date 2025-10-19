#ifndef D03B856A_D060_4755_B4AB_C933DAC4B6FB
#define D03B856A_D060_4755_B4AB_C933DAC4B6FB
#include "enum.h"

namespace ChatGPTAI
{
    constexpr auto API_URL = "https://api.openai.com/v1/responses";
    constexpr auto API_HEADER_CONTENTTYPE = "Content-Type: application/json";

    constexpr auto KEY_MODEL = "model";
    constexpr auto KEY_INPUT = "input";

    struct ChatPrompt
    {
        std::string role = "user";
        std::string content;
    };

    class Client
    {
    public:
        explicit Client(const std::string& apiKey, Model model = Model::GPT4o_Mini);

        EResultValue<Response> chat(const std::string& userMessages);
        void resetMemory();

    private:
        Client(const Client&) = delete;
        Client& operator=(const Client&) = delete;
        Client(Client&&) = delete;
        Client& operator=(Client&&) = delete;

        Model m_model;
        std::string m_apiKey;
        std::string m_lastId;
        std::vector<ChatPrompt> m_messages;
    };
} // namespace ChatGPTAI
#endif /* D03B856A_D060_4755_B4AB_C933DAC4B6FB */
