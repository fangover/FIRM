#ifndef B277F9FC_D020_42D4_AC4F_91F2991F7F7A
#define B277F9FC_D020_42D4_AC4F_91F2991F7F7A

#include <common/globalEnum.h>
#include <eresult.h>

namespace Strategies
{
    class IExecutor
    {
    public:
        virtual EResult execute(const Signal&) = 0;
    };
} // namespace Strategies

#endif /* B277F9FC_D020_42D4_AC4F_91F2991F7F7A */
