#ifndef GX_BASEPTR_H
#define GX_BASEPTR_H

/*
    This 'BasePtr' class represents as pointer object. To use this class user should provide a StoragePolicy and a
    DestuctPolicy.

    TODO: Add supports for user defined allocator
 */

#include "DefaultStorage.h"
#include "DefaultAllocator.h"

namespace GX
{
    template<
        typename ValueType,
        template <typename> class AllocatorPolicy = DefaultAllocator,
        template <typename> class StoragePolicy = DefaultStorage
    >
    class BasePtr
    {
    public:
        typedef BasePtr                                         Super;
        typedef StoragePolicy<ValueType>                        StorageType;
        typedef AllocatorPolicy<ValueType>                      AllocatorType;
        typedef typename StorageType::PointerType               PointerType;
        typedef typename StorageType::ReferenceType             ReferenceType;

        BasePtr()
            : m_storage(nullptr)
        {
        }

        BasePtr(PointerType pointer)
            : m_storage(pointer)
        {
        }
        
        BasePtr(const StorageType& storage)
            : m_storage(storage)
        {
        }

        BasePtr(BasePtr&& right)
            : m_storage(std::move(right.m_storage))
        {}

        BasePtr& operator = (const BasePtr& right)
        {
            m_storage = right.m_storage;
            return *this;
        }

        BasePtr& operator = (BasePtr&& right)
        {
            swap(m_storage, right.m_storage);

            return *this;
        }

        virtual ~BasePtr() {};

        PointerType getPtr()
        {
            return m_storage.getPtr();
        }

        PointerType getPtr() const
        {
            return m_storage.getPtr();
        }

        PointerType* getPtrPtr()
        {
            return m_storage.getPtrPtr();
        }

        PointerType const* getPtrPtr() const
        {
            return m_storage.getPtrPtr();
        }

        ReferenceType getRef()
        {
            return m_storage.getRef();
        }

        ReferenceType getRef() const
        {
            return m_storage.getRef();
        }

        PointerType operator->()
        {
            return m_storage.getPtr();
        }

        PointerType operator->() const
        {
            return m_storage.getPtr();
        }

        ReferenceType operator*()
        {
            return m_storage.getRef();
        }

        ReferenceType operator*() const
        {
            return m_storage.getRef();
        }

        explicit operator bool() const
        {
            return getPtr() != 0;
        }

        bool operator == (const BasePtr& right) const
        {
            return getPtr() == right.getPtr();
        }

        bool operator != (const BasePtr& right) const
        {
            return getPtr() != right.getPtr();
        }

        void release()
        {
            free(m_storage.getPtr());
            m_storage = 0;
        }

        template<typename ... ArgTypes>
        static ValueType* alloc(const ArgTypes& ... args)
        {
            return AllocatorType::alloc(args ...);
        }

        static void free(PointerType pointer)
        {
            AllocatorType::free(pointer);
        }

    protected:
        StorageType m_storage;
    };
}
#endif