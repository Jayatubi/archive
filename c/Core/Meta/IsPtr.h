#ifndef GX_META_ISPTR_H
#define GX_META_ISPTR_H

/*
    This meta class is used to check if a type is pointer or not.

    Example:
        
        Meta::IsPtr<int>::Result;           // Result is: false
        Meta::IsPtr<int*>::Result;          // Result is: true
 */

namespace GX
{
    namespace Meta
    {
        template<typename ValueType>
        struct IsPtr
        {
            enum { Result = std::is_pointer<ValueType>::value };
        };
        
        template<typename ValueType>
        struct AddPtr
        {
            typedef ValueType* Result;
        };

        template<typename ValueType>
        struct AddPtr<ValueType*>
        {
            typedef ValueType* Result;
        };

        template<typename ValueType>
        struct RemovePtr
        {
            typedef ValueType Result;
        };

        template<typename ValueType>
        struct RemovePtr<ValueType*>
        {
            typedef ValueType Result;
        };
    }
}

#endif