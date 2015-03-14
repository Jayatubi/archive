#ifndef GX_META_ISFLOAT_H
#define GX_META_ISFLOAT_H

#include "Result.h"
#include "Const.h"

namespace GX
{
    namespace Meta
    {
        template<typename ValueType>
        struct IsFloat
        {
            enum { Result = std::is_floating_point<ValueType>::value };
        };
    }
}

#endif