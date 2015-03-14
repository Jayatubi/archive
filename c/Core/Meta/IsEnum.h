#ifndef GX_META_ISENUM_H
#define GX_META_ISENUM_H

namespace GX
{
    namespace Meta
    {
        template < typename ValueType >
        struct IsEnum
        {
            enum
            {
                Result = __is_enum(ValueType)
            };
        };
    }
}

#endif // GX_META_ISENUM_H
