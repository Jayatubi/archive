#ifndef GX_DEFAULTALLOCATOR_H
#define GX_DEFAULTALLOCATOR_H

namespace GX
{
    template<typename ValueType>
    struct DefaultAllocator
    {
        static ValueType* alloc()
        {
            return new ValueType();
        }

        static void free(ValueType* pointee)
        {
            if (pointee != 0)
            {
                delete pointee;
                pointee = 0;
            }
        }
    };
}

#endif // GX_DEFAULTALLOCATOR_H