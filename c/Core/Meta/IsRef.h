#ifndef GX_META_ISREF_H
#define GX_META_ISREF_H

/*
    This meta class is used to check if a type is reference or not.

    Example:
        
        Meta::IsRef<int>::Result;           // Result is: false
        Meta::IsRef<int&>::Result;          // Result is: true
 */

namespace GX
{
    namespace Meta
    {
        template<typename ValueType>
        struct IsRef
        {
            enum { Result = std::is_reference<ValueType>::value };
        };
        
        template<typename ValueType>
        struct AddRef
        {
            typedef ValueType& Result;
        };

        template<typename ValueType>
        struct AddRef<ValueType&>
        {
            typedef ValueType& Result;
        };

        template<typename ValueType>
        struct RemoveRef
        {
            typedef ValueType Result;
        };

        template<typename ValueType>
        struct RemoveRef<ValueType&>
        {
            typedef ValueType Result;
        };
    }
}

#endif