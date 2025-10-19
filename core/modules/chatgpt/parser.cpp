#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include "parser.h"

using namespace rapidjson;
using namespace ChatGPTAI;

namespace
{
    inline const char* getStringOr(const Value& v, const char* key, const char* def = "")
    {
        if (v.HasMember(key) && v[key].IsString())
        {
            return v[key].GetString();
        }
        return def;
    }

    inline int getIntOr(const Value& v, const char* key, int def = 0)
    {
        if (v.HasMember(key) && v[key].IsInt())
        {
            return v[key].GetInt();
        }
        if (v.HasMember(key) && v[key].IsInt64())
        {
            return static_cast<int>(v[key].GetInt64());
        }
        return def;
    }

    inline bool getBoolOr(const Value& v, const char* key, bool def = false)
    {
        if (v.HasMember(key) && v[key].IsBool())
        {
            return v[key].GetBool();
        }
        return def;
    }

} // namespace

bool RJsonParser::parseResponse(const std::string& jsonStr, Response& r)
{
    Document d;
    if (d.Parse(jsonStr.c_str()).HasParseError())
    {
        return false;
    }

    r.id = getStringOr(d, "id");
    r.object = getStringOr(d, "object");
    r.created_at = d.HasMember("created_at") && d["created_at"].IsInt64() ? d["created_at"].GetInt64() : 0;
    r.status = getStringOr(d, "status");
    r.background = getBoolOr(d, "background");
    r.model = getStringOr(d, "model");

    if (d.HasMember("error"))
    {
        if (d["error"].IsString())
        {
            r.error = std::string(d["error"].GetString());
        }
        else if (d["error"].IsObject() && d["error"].HasMember("message") && d["error"]["message"].IsString())
        {
            r.error = std::string(d["error"]["message"].GetString());
        }
    }

    if (d.HasMember("billing") && d["billing"].IsObject())
    {
        const auto& b = d["billing"];
        r.billing.payer = getStringOr(b, "payer");
    }

    if (d.HasMember("usage") && d["usage"].IsObject())
    {
        const auto& u = d["usage"];
        r.usage.input_tokens = getIntOr(u, "input_tokens");
        r.usage.output_tokens = getIntOr(u, "output_tokens");
        r.usage.total_tokens = getIntOr(u, "total_tokens");
    }

    if (d.HasMember("output") && d["output"].IsArray())
    {
        for (auto& msg : d["output"].GetArray())
        {
            Message m;
            m.id = getStringOr(msg, "id");
            m.type = getStringOr(msg, "type");
            m.status = getStringOr(msg, "status");
            m.role = getStringOr(msg, "role");

            if (msg.HasMember("content") && msg["content"].IsArray())
            {
                for (auto& c : msg["content"].GetArray())
                {
                    OutputText ot;
                    ot.type = getStringOr(c, "type");
                    ot.text = getStringOr(c, "text");
                    m.content.emplace_back(std::move(ot));
                }
            }
            r.output.emplace_back(std::move(m));
        }
    }

    return true;
}

std::string RJsonParser::serializeResponse(const Response& r)
{
    StringBuffer sb;
    Writer<StringBuffer> w(sb);

    w.StartObject();
    w.Key("id");
    w.String(r.id.c_str());
    w.Key("object");
    w.String(r.object.c_str());
    w.Key("created_at");
    w.Int64(r.created_at);
    w.Key("status");
    w.String(r.status.c_str());
    w.Key("background");
    w.Bool(r.background);
    w.Key("model");
    w.String(r.model.c_str());

    if (r.error.has_value())
    {
        w.Key("error");
        w.String(r.error->c_str());
    }

    w.Key("billing");
    w.StartObject();
    w.Key("payer");
    w.String(r.billing.payer.c_str());
    w.EndObject();

    w.Key("usage");
    w.StartObject();
    w.Key("input_tokens");
    w.Int(r.usage.input_tokens);
    w.Key("output_tokens");
    w.Int(r.usage.output_tokens);
    w.Key("total_tokens");
    w.Int(r.usage.total_tokens);
    w.EndObject();

    w.Key("output");
    w.StartArray();
    for (const auto& m : r.output)
    {
        w.StartObject();
        w.Key("id");
        w.String(m.id.c_str());
        w.Key("type");
        w.String(m.type.c_str());
        w.Key("status");
        w.String(m.status.c_str());
        w.Key("role");
        w.String(m.role.c_str());
        w.Key("content");
        w.StartArray();
        for (const auto& ot : m.content)
        {
            w.StartObject();
            w.Key("type");
            w.String(ot.type.c_str());
            w.Key("text");
            w.String(ot.text.c_str());
            w.EndObject();
        }
        w.EndArray();
        w.EndObject();
    }
    w.EndArray();

    w.EndObject();
    return sb.GetString();
}
