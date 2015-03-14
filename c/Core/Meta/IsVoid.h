#ifndef GX_META_ISVOID_H
#define GX_META_ISVOID_H

#include "Result.h"

namespace GX
{
    namespace Meta
    {
        template < typename ValueType >
        struct IsVoid
        {
            enum { Result = std::is_void<ValueType>::value };
        };
    }
}

#endif // GX_META_ISVOID_H
