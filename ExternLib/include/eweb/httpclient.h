#ifndef A1A26C89_0FE9_42ED_BEBE_C6CF29E56BD7
#define A1A26C89_0FE9_42ED_BEBE_C6CF29E56BD7

#include <curl/curl.h>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
    {
        std::string* s = static_cast<std::string*>(userp);
        s->append(static_cast<char*>(contents), size * nmemb);
        return size * nmemb;
    }
} // namespace

namespace EWeb
{
    struct HttpResponse
    {
        int statusCode = 0;
        std::string body;
    };

    class HttpClient
    {
    public:
        static HttpResponse post(const std::string& url,
                                 const std::string& payload,
                                 const std::vector<std::string>& headers,
                                 long timeoutMs)
        {
            CURL* curl = curl_easy_init();
            if (!curl)
            {
                throw std::runtime_error("Failed to init curl");
            }

            std::string response;
            struct curl_slist* headerList = nullptr;
            for (const auto& h : headers)
            {
                headerList = curl_slist_append(headerList, h.c_str());
            }

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, timeoutMs);
            curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

            auto res = curl_easy_perform(curl);
            if (res != CURLE_OK)
            {
                curl_slist_free_all(headerList);
                curl_easy_cleanup(curl);
                throw std::runtime_error(curl_easy_strerror(res));
            }

            long httpCode = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
            curl_slist_free_all(headerList);
            curl_easy_cleanup(curl);

            return { static_cast<int>(httpCode), std::move(response) };
        }

        static HttpResponse del(const std::string& url, const std::vector<std::string>& headers)
        {
            CURL* curl = curl_easy_init();
            if (!curl)
            {
                throw std::runtime_error("Failed to init curl");
            }

            std::string response;
            struct curl_slist* headerList = nullptr;
            for (const auto& h : headers)
            {
                headerList = curl_slist_append(headerList, h.c_str());
            }

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            auto res = curl_easy_perform(curl);
            if (res != CURLE_OK)
            {
                curl_slist_free_all(headerList);
                curl_easy_cleanup(curl);
                throw std::runtime_error(curl_easy_strerror(res));
            }

            long httpCode = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
            curl_slist_free_all(headerList);
            curl_easy_cleanup(curl);

            return { static_cast<int>(httpCode), std::move(response) };
        }
    };

} // namespace EWeb

#endif /* A1A26C89_0FE9_42ED_BEBE_C6CF29E56BD7 */
