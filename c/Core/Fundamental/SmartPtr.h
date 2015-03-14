#ifndef GX_SMARTPTR_H
#define GX_SMARTPTR_H

/*
    This 'SmartPtr' class represents as a self reference count managed pointer. It would destroy the pointer stored
    inside it when it finds the reference count has been decreased to 0.
 */
#include "../BasicType/BasicType.h"
#include "../Fundamental/Assert.h"
#include "BasePtr.h"
#include "DefaultAllocator.h"

namespace GX
{
    template<typename Allocator>
    class DefaultRefCount
    {
    public:
        DefaultRefCount() : m_pRefCount(0)
        {
            m_pRefCount = Allocator::alloc();
            *m_pRefCount = 1;
        }
    
        DefaultRefCount(const DefaultRefCount& right)
            : m_pRefCount(right.m_pRefCount)
        {
            increase();
        }

        DefaultRefCount(DefaultRefCount&& right)
            : m_pRefCount(right.m_pRefCount)
        {
            right.m_pRefCount = 0;
        }
    
        DefaultRefCount& operator = (const DefaultRefCount& right)
        {
            release();
            
            m_pRefCount = right.m_pRefCount;
            
            increase();

            return *this;
        }
    
        DefaultRefCount& operator = (DefaultRefCount&& right)
        {
            swap(m_pRefCount, right.m_pRefCount);

            return *this;
        }

        ~DefaultRefCount()
        {
            release();
        }
    
        GX::U32 release()
        {
            GX::U32 result = 0;

            if (m_pRefCount != 0)
            {
                (*m_pRefCount)--;
                result = *m_pRefCount;

                if (*m_pRefCount == 0)
                {
                    Allocator::free(m_pRefCount);
                }

                m_pRefCount = 0;
            }
            
            return result;
        }

        GX::U32 increase()
        {
            GX::U32 result = 0;
            GX_ASSERT(m_pRefCount != NULL, "Invalid ref count");
            if (m_pRefCount != 0)
            {
                (*m_pRefCount)++;
                result = *m_pRefCount;
            }
            return result;
        }
    
        GX::U32 getRefCount()
        {
            return m_pRefCount != 0 ? *m_pRefCount : 0;
        }
    
    private:
        GX::U32* m_pRefCount;
    };	
    
    template
    <
        typename ValueType,
        template <typename> class AllocatorPolicy = DefaultAllocator,
        template <typename> class StoragePolicy = DefaultStorage,
        typename OwnerShipPolicy = DefaultRefCount< MemoryPoolAllocatorAlias<U32> >
    >
    class SmartPtr : public BasePtr<ValueType, AllocatorPolicy, StoragePolicy>
    {
    public:
        typedef BasePtr<ValueType, AllocatorPolicy, StoragePolicy>  Super;
        typedef typename Super::PointerType                         PointerType;

        SmartPtr()
            : Super(0)
        {
        }

        SmartPtr(PointerType pointer)
            : Super(pointer)
        {}
    
        SmartPtr(const SmartPtr& right)
            : m_refCount(right.m_refCount)
            , Super(right.m_storage)
        {}

        SmartPtr& operator = (const SmartPtr& right)
        {
            release();
            m_refCount = right.m_refCount;
            Super::m_storage = right.m_storage;
    
            return *this;
        }

        virtual ~SmartPtr()
        {
            release();
        }

    private:
        void release()
        {
            if (m_refCount.release() == 0)
            {
                Super::release();
            }
        }
    
    private:
        OwnerShipPolicy m_refCount;
    };
}
#endif