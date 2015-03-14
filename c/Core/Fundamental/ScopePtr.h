#ifndef GX_SCOPEPTR_H
#define GX_SCOPEPTR_H

/*
    This 'ScopePtr' class represents as a self destroy pointer. It would destroy the pointer stored inside it as well 
    as the class destruct.
 */

#include "BasePtr.h"

namespace GX
{
	template<
        typename ValueType,
        template <class> class StoragePolicy = DefaultStorage,
        template <class> class AllocatorPolicy = DefaultAllocator
    >
    class ScopePtr : public BasePtr<ValueType, StoragePolicy, AllocatorPolicy>
    {
    public:
        typedef BasePtr<ValueType, StoragePolicy, AllocatorPolicy>   Super;
        typedef typename Super::PointerType                         PointerType;

        explicit ScopePtr(PointerType pointer)
            : Super(pointer)
        {
        }

        virtual ~ScopePtr()
        {
            Super::free();
        }
    };
}
#endif