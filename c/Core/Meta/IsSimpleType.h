#ifndef GX_META_ISSIMPLETYPE_H
#define GX_META_ISSIMPLETYPE_H

#include "Result.h"
#include "IsPtr.h"
#include "IsPOD.h"

namespace GX
{
    namespace Meta
    {
        template < typename ValueType >
        struct IsSimpleType : public IfThenElse
            <
                (IsPOD<ValueType>::Result  || IsClass<ValueType>::Result) && !IsPtr<ValueType>::Result,
                TrueType,
                FalseType
            >::Result
        {};
    }
}
#endif // GX_META_ISSIMPLETYPE_H
