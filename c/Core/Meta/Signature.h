#ifndef GX_META_SIGNATURE_H
#define GX_META_SIGNATURE_H

/*
    This meta class is used to extract the return type and parameters' types from a function type.

    Example:

        typedef Meta::Signature<void(int, float)> MySignature;

        MySignature::Result;        // Result is: void
        MySignature::ParamType0;    // Result is: int
        MySignature::ParamType1;    // Result is: float
 */

#include "Tuple.h"

namespace GX
{
    namespace Meta
    {
        template<typename>
        struct Signature;

        template<typename _ResultType, typename ... ArgTypes>
        struct Signature<_ResultType(*)(ArgTypes ... )>
        {
            typedef _ResultType             ResultType;
            typedef Tuple<ArgTypes ... >    ParamType;

            template<U32 Index>
            struct Arg
            {
                typedef typename TupleAt<Index, ParamType>::ValueType ValueType;
            };
        };
    }
}

#endif