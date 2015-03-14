#ifndef _GX_ENABLEIF_H_
#define _GX_ENABLEIF_H_

namespace GX
{
    namespace Meta
    {
        template < bool test >
        struct EnableIf
        {
        };

        template <>
        struct EnableIf<true>
        {
            typedef void* Result;
        };
    }
}


#endif