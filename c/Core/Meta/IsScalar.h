#ifndef GX_META_ISSCALAR_H
#define GX_META_ISSCALAR_H

#include "Result.h"
#include "../BasicType/BasicType.h"

namespace GX
{
    namespace Meta
    {
        template< typename ValueType >
        struct IsScalar
        {
            enum { Result = std::is_scalar<ValueType>::value };
        };
    }
}

#endif // GX_META_ISSCALAR_H
