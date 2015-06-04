#ifndef GXANY_H__
#define GXANY_H__

namespace GX
{
    class PlaceHolder
    {
    public:
        virtual ~PlaceHolder() {}
        virtual PlaceHolder* clone() const = 0;
        virtual void release() = 0;
    };

    template<
        typename ValueType,
        typename AllocatorPolicy = MemoryPoolAllocator
    >
    class Holder : public PlaceHolder
    {
    public:
        typedef AllocatorPolicy         AllocatorType;

        Holder(const ValueType& value)
        : m_held(value)
        {}
        
        ~Holder(){}

        ValueType* get()
        {
            return &m_held;
        }

        const ValueType* get() const
        {
            return m_held;
        }
        
        virtual Holder* clone() const
        {
            return alloc(m_held);
        }

        virtual void release()
        {
            free(this);
        }

        template<typename ... ArgTypes>
        static Holder* alloc(ArgTypes ... args)
        {
            return AllocatorType::template alloc<Holder>(args ...);
        }

        static void free(Holder* value)
        {
            AllocatorType::free(value);
        }

    private:
        ValueType m_held;
    };

    template<typename AllocatorPolicy = MemoryPoolAllocator>
    class AnyImpl
    {
    public:
        AnyImpl()
        : m_pContent(nullptr)
        {}

        template<typename ValueType>
        AnyImpl(const ValueType& value)
        : m_pContent(Holder<ValueType, AllocatorPolicy>::alloc(value))
        {}

        AnyImpl(const AnyImpl& right)
        : m_pContent(right.m_pContent != nullptr ? right.m_pContent->clone() : nullptr)
        {}

        AnyImpl(AnyImpl&& right)
        : m_pContent(right.m_pContent)
        {
            right.m_pContent = nullptr;
        }

        ~AnyImpl()
        {
            release();
        }
        
        bool empty() const 
        {
            return m_pContent == nullptr;
        }

        template<typename ValueType>
        AnyImpl& operator = (const ValueType& value)
        {
            release();
            m_pContent = Holder<ValueType, AllocatorPolicy>::alloc(value);
            return *this;
        }

        AnyImpl& operator = (const AnyImpl& right)
        {
            release();
            m_pContent = right.m_pContent->clone();
            return *this;
        }

        AnyImpl& operator = (AnyImpl&& right)
        {
            release();
            m_pContent = right.m_pContent;
            right.m_pContent = nullptr;
            return *this;
        }

        template<typename ValueType>
        operator const ValueType& () const
        {
            const ValueType* pResult = operator const ValueType* ();

            // GX_ASSERT(pResult != nullptr, "AnyImpl cast failed");

            return *pResult;
        }

        template<typename ValueType>
        operator ValueType& ()
        {
            ValueType* pResult = operator ValueType* ();
            
            // GX_ASSERT(pResult != nullptr, "AnyImpl cast failed");
            
            return *pResult;
        }
        
        template<typename ValueType>
        operator const ValueType* () const
        {
            return m_pContent != nullptr ? static_cast< Holder<ValueType, AllocatorPolicy>* >(m_pContent)->get() : nullptr;
        }
            
        template<typename ValueType>
        operator ValueType* ()
        {
            return m_pContent != nullptr ? static_cast< Holder<ValueType, AllocatorPolicy>* >(m_pContent)->get() : nullptr;
        }
            
        template<typename ValueType>
        ValueType *getContentPtr()
        {
            return m_pContent != nullptr ? static_cast< Holder<ValueType, AllocatorPolicy>* >(m_pContent)->get() : nullptr;
        }
            
        template<typename ValueType>
        const ValueType *getContentPtr()const
        {
            return m_pContent != nullptr ? static_cast< Holder<ValueType, AllocatorPolicy>* >(m_pContent)->get() : nullptr;
        }
            
        void release()
        {
            if (m_pContent != nullptr)
            {
                m_pContent->release();
            }
        }

    private:
        PlaceHolder* m_pContent;
    };

    typedef AnyImpl<>   Any;
}

#endif