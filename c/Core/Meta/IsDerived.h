#ifndef GX_META_ISDERIVED_H
#define GX_META_ISDERIVED_H

/*
    This meta class is used to determine if a class is derived from another class.

    Example:

        Class A;
        Class B : public Class A;
        Class C;

        Meta::IsDerived<A, B>::Result;          // Result is: true
        Meta::IsDerived<A, C>::Result;          // Result is: false
 */
#include "Result.h"

namespace GX
{
    namespace Meta
    {
        template<typename BaseType, typename DerivedType>
        struct IsDerived
        {
            enum { Result = std::is_base_of<BaseType, DerivedType>::value };
        };
    }
}

#endif