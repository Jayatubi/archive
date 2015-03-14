#ifndef GXARRAY_H__
#define GXARRAY_H__

#include <array>
#include "BasicType.h"

namespace GX
{    
    template<typename ValueType, int ArraySize>
    class Array : public std::array<ValueType, ArraySize>
    {
    public:
        typedef std::array<ValueType, ArraySize> BaseType;
        typedef typename BaseType::iterator          Iterator;
        typedef typename BaseType::const_iterator    ConstIterator;

    public:
        static const U32 Size = ArraySize;

        Array()
        : BaseType()
        {}

        template<typename SrcType, U32 SrcCount>
        Array(const SrcType (&src)[SrcCount])
        {
            initFrom(src);
        }

        template<typename SrcType>
        Array(const std::initializer_list<SrcType>& data)
        {
            auto iter = data.begin();
            U32 index = 0;

            while(index < ArraySize)
            {
                BaseType::at(index++) = iter != data.end() ? ValueType(*(iter++)) : ValueType();
            }
        }

        template<typename SrcType, U32 SrcCount>
        Array& operator=(const SrcType(&src)[SrcCount])
        {
            initFrom(src);
            return *this;
        }

        template<typename SrcType, U32 SrcCount>
        void initFrom(const SrcType(&src)[SrcCount])
        {
            for(U32 i = 0; i < Meta::Min<ArraySize, SrcCount>::Result; i++)
            {
                BaseType::at(i) = src[i];
            }
        }

        template<typename UnaryFunc>
        Iterator find(const UnaryFunc& func)
        {
            Iterator iter = BaseType::begin();
            Iterator end  = BaseType::end();

            for(; iter != end && !func(*iter); ++iter);

            return iter;
        }

        template<typename UnaryFunc>
        ConstIterator find(const UnaryFunc& func) const
        {
            ConstIterator iter = BaseType::begin();
            ConstIterator end  = BaseType::end();

            for(; iter != end && !func(*iter); ++iter);

            return iter;
        }

        Iterator find(const ValueType& value)
        {
            Iterator iter = BaseType::begin();
            Iterator _end  = BaseType::end();

            for(; iter != _end && !(*iter == value); ++iter);

            return iter;
        }

        ConstIterator find(const ValueType& value) const
        {
            ConstIterator iter = BaseType::begin();
            ConstIterator _end  = BaseType::end();

            for(; iter != _end && !(*iter == value); ++iter);

            return iter;
        }

        template<typename UnaryFunc>
        ConstIterator findIf(const UnaryFunc& func) const
        {
            ConstIterator iter = BaseType::begin();
            ConstIterator _end  = BaseType::end();

            for(; iter != _end; ++iter)
                if (func(*iter))
                    return iter;
            
            return _end;
        }

        bool contains(const ValueType& value) const
        {
            return find(value) != BaseType::end();
        }

        template<typename FuncType>
        void foreach(const FuncType& func)
        {
            Iterator iter = BaseType::begin();
            Iterator _end  = BaseType::end();

            for(; iter != _end; ++iter)
            {
                func(*iter);
            }
        }

        void sort()
        {
            std::sort(BaseType::begin(), BaseType::end());
        }

        template<typename PredType>
        void sort(const PredType& pred)
        {
            std::sort(BaseType::begin(), BaseType::end(), pred);
        }
    };

    template<typename ValueType, U32 SrcCount>
    static Array<ValueType, SrcCount> MakeArray(const ValueType(&src)[SrcCount])
    {
        return Array<ValueType, SrcCount>(src);
    }

    template<typename First, typename ... Rest>
    static Array<First, 1 + sizeof ... (Rest)> MakeArray(const First& first, const Rest& ... rest)
    {
        return Array<First, 1 + sizeof ... (Rest)>({first, rest ...});
    }

    template<typename ValueType, typename First, typename ... Rest>
    static Array<ValueType, 1 + sizeof ... (Rest)> MakeArrayEx(const First& first, const Rest& ... rest)
    {
        return Array<ValueType, 1 + sizeof ... (Rest)>({first, rest ...});
    }
}

#endif