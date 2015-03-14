#ifndef GX_AUTOPTR_H
#define GX_AUTOPTR_H

#include "BasePtr.h"

namespace GX
{
    template
        <
        typename ValueType,
        template <class> class AllocatorPolicy = DefaultAllocator,
        template <class> class StoragePolicy = DefaultStorage
        >
    class AutoPtr : public BasePtr<ValueType, AllocatorPolicy, StoragePolicy>
    {
    public:
        typedef BasePtr<ValueType, AllocatorPolicy, StoragePolicy> Super;

        AutoPtr()
            : Super(0)
        {}

        AutoPtr(typename Super::PointerType pointer)
            : Super(pointer)
        {}

        virtual ~AutoPtr()
        {
            release();
        }

        AutoPtr& operator=(typename Super::PointerType pointer)
        {
            if (Super::getPtr() != pointer)
            {
                release();
                Super::m_storage = pointer;
            }
            return *this;
        }

        AutoPtr& reconstruct()
        {
            release();
            Super::m_storage = Super::alloc();

            return *this;
        }

    private:
        // No copy constructor allowed
        AutoPtr(const AutoPtr& right)
            : Super(right.m_storage)
        {}

        void release()
        {
            Super::release();
        }
    };
}

#endif