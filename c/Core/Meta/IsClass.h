#ifndef GX_META_ISCLASS_H
#define GX_META_ISCLASS_H

#include "Result.h"

namespace GX
{
    namespace Meta
    {
        template < typename ValueType >
        struct IsClass
        {
            enum { Result = std::is_class<ValueType>::value };
        };
    }
}
#endif // GX_META_ISCLASS_H
