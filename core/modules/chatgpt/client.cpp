#include "eweb/httpclient.h"
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include "client.h"
#include "enum.h"
#include "parser.h"

using namespace ChatGPTAI;

namespace
{
    inline rapidjson::Value ToJsonArray(const std::vector<ChatPrompt>& msgs, rapidjson::Document::AllocatorType& alloc)
    {
        rapidjson::Value arr(rapidjson::kArrayType);
        for (const auto& m : msgs)
        {
            rapidjson::Value obj(rapidjson::kObjectType);
            obj.AddMember("role",
                          rapidjson::Value(m.role.c_str(), static_cast<rapidjson::SizeType>(m.role.size()), alloc),
                          alloc);
            obj.AddMember(
                "content",
                rapidjson::Value(m.content.c_str(), static_cast<rapidjson::SizeType>(m.content.size()), alloc),
                alloc);
            arr.PushBack(obj, alloc);
        }
        return arr; // NRVO
    }

}; // namespace

Client::Client(const std::string& apiKey, Model model) : m_model(std::move(model)), m_apiKey(std::move(apiKey))
{
    m_messages.reserve(16);
}

EResultValue<Response> Client::chat(const std::string& userMessages)
{
    LOG_ENTRY;

    m_messages.emplace_back("user", userMessages);

    auto fnBuildAndPost = [&]() -> EWeb::HttpResponse
    {
        rapidjson::Document payload;
        payload.SetObject();
        auto& alloc = payload.GetAllocator();

        const std::string modelStr = to_string(m_model);
        payload.AddMember(rapidjson::StringRef(KEY_MODEL),
                          rapidjson::Value(modelStr.c_str(), static_cast<rapidjson::SizeType>(modelStr.size()), alloc),
                          alloc);

        payload.AddMember(rapidjson::StringRef(KEY_INPUT), ToJsonArray(m_messages, alloc), alloc);

        rapidjson::StringBuffer sb;
        rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
        payload.Accept(writer);

        std::vector<std::string> headers = { API_HEADER_CONTENTTYPE, "Authorization: Bearer " + m_apiKey };

        return EWeb::HttpClient::post(API_URL, sb.GetString(), headers, 30000);
    };

    auto response = fnBuildAndPost();
    if (response.statusCode < 200 || response.statusCode >= 300)
    {
        Response r;
        if (RJsonParser::parseResponse(response.body, r))
        {
            if (!r.error.has_value())
            {
                r.error = "HTTP " + std::to_string(response.statusCode);
            }
            return EResultValue<Response>::ok(r);
        }
        return EResultValue<Response>::fail("AI API HTTP error " + std::to_string(response.statusCode));
    }

    Response r;
    if (!RJsonParser::parseResponse(response.body, r))
    {
        return EResultValue<Response>::fail("Failed to parse AI API response JSON");
    }

    m_messages.emplace_back("assistant", r.output[0].content[0].text);
    return EResultValue<Response>::ok(r);
}

void Client::resetMemory()
{
    LOG_ENTRY;

    std::string url = API_URL + m_lastId;
    std::vector<std::string> headers = { API_HEADER_CONTENTTYPE, "Authorization: Bearer " + m_apiKey };
    LOG(EWeb::HttpClient::del(url, headers).body);
}