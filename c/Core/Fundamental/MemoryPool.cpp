#include "MemoryPool.h"

void* cc_malloc(unsigned size)
{
    return GX::MemoryPoolAllocator::allocImpl(size);
}

void  cc_free(void* pointer)
{
    if (pointer != nullptr)
    {
        CC_MemoryTag& tag = *(CC_MemoryTag*)(pointer);
        GX::MemoryPoolAllocator::freeImpl((GX::U8*)pointer, tag.alloc_size);
    }
}