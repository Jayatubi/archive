#ifndef GX_TUPLE_H
#define GX_TUPLE_H

#include "BasicType.h"

namespace GX {

    template<typename ... ValueTypes> class Tuple;

    template<> class Tuple<>
    {
    public:
        enum { ValueCount = 0  };

        Tuple()
        {}

        bool operator < (const Tuple& right) const
        {
            return false;
        }
    };

    template<typename ThisType>
    class Tuple<ThisType> : public Tuple<>
    {
    public:
        typedef ThisType ValueType;
        typedef Tuple<ThisType> ThisTupleType;

        enum { ValueCount = 1  };

        Tuple()
        {}

        Tuple(const ValueType& value)
        : m_value(value)
        {}

        ValueType& value() { return m_value;}
        const ValueType& value() const { return m_value; }

        bool operator < (const Tuple& right) const
        {
            return m_value < right.m_value;
        }

    protected:
        ValueType m_value;
    };

    template<typename ThisType, typename ... RestType>
    class Tuple<ThisType, RestType ... > : public Tuple< RestType ... >
    {
    public:
        typedef ThisType ValueType;
        typedef Tuple< RestType ... >           BaseTupleType;
        typedef Tuple<ThisType, RestType ... >  ThisTupleType;

        enum { ValueCount = BaseTupleType::ValueCount + 1 };

        Tuple()
        : BaseTupleType()
        {}

        Tuple(const ValueType& value, const RestType& ... rest)
        : m_value(value)
        , BaseTupleType(rest ... )
        {}

        ValueType& value() { return m_value;}
        const ValueType& value() const { return m_value; }

        bool operator < (const Tuple& right) const
        {
            return m_value < right.m_value || (m_value == right.m_value && static_cast<BaseTupleType>(*this) < static_cast<BaseTupleType>(right));
        }

    private:
        ValueType m_value;
    };

    template<U32 Index, typename ... ValueTypes> struct TupleAt;

    template<typename ThisType, typename ... RestType>
    struct TupleAt< 0, Tuple< ThisType, RestType ... > >
    {
        typedef ThisType                        ValueType;
        typedef Tuple< ThisType, RestType ... > TupleType;
    };

    template<U32 Index, typename ThisType, typename ... RestType>
    struct TupleAt< Index, Tuple< ThisType, RestType ... > >
    {
        typedef typename TupleAt< Index - 1, Tuple< RestType ... > >::ValueType ValueType;
        typedef typename TupleAt< Index - 1, Tuple< RestType ... > >::TupleType TupleType;
    };

    template<U32 Index, typename ... ValueTypes>
    typename TupleAt<Index, Tuple< ValueTypes ... > >::ValueType&
    getTuple(Tuple< ValueTypes ... >& tuple)
    {
        typedef typename TupleAt<Index, Tuple< ValueTypes ... > >::TupleType BaseTupleType;

        return static_cast<BaseTupleType&>(tuple).value();
    }

    template<U32 Index, typename ... ValueTypes>
    const typename TupleAt<Index, Tuple< ValueTypes ... > >::ValueType&
    getTuple(const Tuple< ValueTypes ... >& tuple)
    {
        typedef typename TupleAt<Index, Tuple< ValueTypes ... > >::TupleType BaseTupleType;

        return static_cast<const BaseTupleType&>(tuple).value();
    }
}

#endif
