#ifndef GXANY_H__
#define GXANY_H__

namespace GX
{
    class PlaceHolder
    {
    public:
        virtual ~PlaceHolder()
        {
        }
        virtual PlaceHolder* clone() const = 0;
    };

    template<typename ValueType>
    class Holder : public PlaceHolder
    {
    public:
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
        
        Holder* clone() const
        {
            return new Holder(m_held);
        }

    private:
        ValueType m_held;
    };

    class Any
    {
    public:
        Any()
        : m_pContent(nullptr)
        {}

        template<typename ValueType>
        Any(const ValueType& value)
        : m_pContent(new Holder<ValueType>(value))
        {}

        Any(const Any& right)
        : m_pContent(right.m_pContent->clone())
        {}

        Any(Any&& right)
        : m_pContent(right.m_pContent)
        {
            right.m_pContent = nullptr;
        }

        ~Any()
        {
            release();
        }
        
        bool empty()const 
        {
            return m_pContent == nullptr;
        }

        template<typename ValueType>
        Any& operator = (const ValueType& value)
        {
            release();
            m_pContent = new Holder<ValueType>(value);
            return *this;
        }

        Any& operator = (const Any& right)
        {
            release();
            m_pContent = right.m_pContent->clone();
            return *this;
        }

        Any& operator = (Any&& right)
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

            GX_ASSERT(pResult != nullptr, "Any cast failed");

            return *pResult;
        }

        template<typename ValueType>
        operator const ValueType* () const
        {
            return m_pContent != nullptr ? static_cast< Holder<ValueType>* >(m_pContent)->get() : nullptr;
        }

        void release()
        {
            if (m_pContent != nullptr)
            {
                delete m_pContent;
            }
        }

    private:
        PlaceHolder* m_pContent;
    };
}

#endif