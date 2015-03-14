#ifndef GX_META_ISARRAY_H
#define GX_META_ISARRAY_H

namespace GX
{
    namespace Meta
    {
        template<typename ValueType>
        struct IsArray
        {
            enum { Result = std::is_array<ValueType>::value };
        };

        template<typename ValueType, int Size>
        constexpr inline int ArraySize(const ValueType (&)[Size])
        {
            return Size;
        };
    }
}

#endif // ISARRAY_H