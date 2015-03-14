#ifndef GX_DEFAULTSTORAGE_H
#define GX_DEFAULTSTORAGE_H

#include "../Meta/IsPtr.h"
#include "../Meta/IsRef.h"

namespace GX
{
    template<typename ValueType>
    class DefaultStorage
    {
    public:
        typedef typename Meta::AddPtr<ValueType>::Result StorageType;
        typedef typename Meta::AddPtr<ValueType>::Result PointerType;
        typedef typename Meta::AddRef<ValueType>::Result ReferenceType;

    public:
        DefaultStorage() 
            : m_pointee(0)
        {}

        DefaultStorage(const StorageType& pointee) 
            : m_pointee(pointee)
        {}

        DefaultStorage& operator = (const DefaultStorage& right)
        {
            m_pointee = right.m_pointee;
            return *this;
        }

        PointerType getPtr() const
        {
            return m_pointee;
        }

        PointerType* getPtrPtr()
        {
            return &m_pointee;
        }

        PointerType const* getPtrPtr() const
        {
            return &m_pointee;
        }

        ReferenceType getRef() const
        {
            return *m_pointee;
        }

        PointerType operator->() const
        {
            return m_pointee;
        }

        ReferenceType operator*() const
        {
            return *m_pointee;
        }

    private:
        StorageType m_pointee;
    };
}

#endif