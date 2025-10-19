#ifndef AB33E1E4_7D76_49C0_9D31_EA577EC1B9DF
#define AB33E1E4_7D76_49C0_9D31_EA577EC1B9DF
#include "enum.h"

namespace ChatGPTAI
{
    class RJsonParser
    {
    public:
        static bool parseResponse(const std::string& json, ChatGPTAI::Response& resp);
        static std::string serializeResponse(const ChatGPTAI::Response& resp);
    };
} // namespace ChatGPTAI

#endif /* AB33E1E4_7D76_49C0_9D31_EA577EC1B9DF */
