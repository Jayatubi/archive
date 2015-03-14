#ifndef GX_META_ISARITHMETIC_H
#define GX_META_ISARITHMETIC_H

#include "IsScalar.h"
#include "IsFloat.h"
#include "IsSame.h"

namespace GX
{
    namespace Meta
    {
        template<typename ValueType>
        struct IsArithmetic
        {
            enum
            {
                Result = std::is_arithmetic<ValueType>::value
            };
        };
    }
}

#endif