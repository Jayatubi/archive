#ifndef GX_META_ISPOD_H
#define GX_META_ISPOD_H

#include "Result.h"
#include "IsVoid.h"
#include "IsScalar.h"
#include "IsEnum.h"
#include "IsPtr.h"
#include "IfThenElse.h"

namespace GX
{
    namespace Meta
    {
        template<typename ValueType>
        struct IsPOD
        {
            enum { Result = std::is_pod<ValueType>::value };
        };
    }
}
#endif // GX_META_ISPOD_H
