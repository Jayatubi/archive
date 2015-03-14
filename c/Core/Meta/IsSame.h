#ifndef GX_META_ISSAME_H
#define GX_META_ISSAME_H

/*
    This meta class is used to check if two types are same;

    Example:

        typedef int TypeA;
        typedef int TypeB;
        typedef long TypeC;

        Meta::IsSame<TypeA, TypeB>::Result;          // Result is: true
        Meta::IsSame<TypeA, TypeC>::Result;          // Result is: false
 */

namespace GX
{
    namespace Meta
    {
        template<typename ValueTypeA, typename ValueTypeB>
        struct IsSame
        {
            enum { Result = std::is_same<ValueTypeA, ValueTypeB>::value };
        };
    }
}

#endif