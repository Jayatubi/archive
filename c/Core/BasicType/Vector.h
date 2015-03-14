#ifndef GXVECTOR_H__
#define GXVECTOR_H__

#include <vector>
#include <algorithm>

namespace GX
{
    template<typename ValueType>
    class Vector : public std::vector<ValueType>
    {
    private:
        typedef std::vector<ValueType> BaseType;
    public:
        typedef typename BaseType::size_type SizeType;
        typedef typename BaseType::const_iterator ConstIterator;
        typedef typename BaseType::iterator Iterator;

        Vector()
        : BaseType()
        {}

        Vector(SizeType initSize)
        : BaseType(initSize)
        {}

        Vector(SizeType initSize, const ValueType& initValue)
        : BaseType(initSize, initValue)
        {}

        template<typename IteratorType>
        Vector(IteratorType begin, IteratorType end)
        : BaseType(begin, end)
        {}

        template<typename SrcType>
        Vector(const std::initializer_list<SrcType>& data)
        {
            auto iter = data.begin();
            auto end  = data.end();

            for(; iter != end; ++iter)
            {
                BaseType::push_back(*iter);
            }
        }

        void copyToBuffer(ValueType* array, U32 count) const
        {
            count = min<U32>(count, BaseType::size());
            for(U32 i = 0; i < count; i++)
            {
                array[i] = (*this)[i];
            }
        }

        template<int ArraySize>
        void copyToArray(ValueType (& array)[ArraySize]) const
        {
            U32 count = min<U32>(ArraySize, BaseType::size());
            copyToBuffer(array, count);
        }

        bool contains(const ValueType& value) const
        {
            return find(value) != BaseType::end();
        }

        template<typename PredicateType>
        bool any(const PredicateType& predicate) const
        {
            bool result = false;
            ConstIterator iter = BaseType::begin();
            ConstIterator end  = BaseType::end();
            for (; iter != end; ++iter)
            {
                if (predicate(*iter))
                {
                    result = true;
                    break;
                }
            }

            return result;
        }

        ConstIterator find(const ValueType& value) const
        {
            ConstIterator iter = BaseType::begin();
            ConstIterator end = BaseType::end();

            for(; iter != end; ++iter)
            {
                if (*iter == value)
                {
                    break;
                }
            }

            return iter;
            //return std::find(BaseType::begin(), BaseType::end(), value);
        }

        Iterator find(const ValueType& value)
        {
            Iterator iter = BaseType::begin();
            Iterator end = BaseType::end();

            for(; iter != end; ++iter)
            {
                if (*iter == value)
                {
                    break;
                }
            }

            return iter;
            //return std::find(BaseType::begin(), BaseType::end(), value);
        }

        template<typename PredicateType>
        ConstIterator findif(const PredicateType& predicate) const
        {
            ConstIterator result = BaseType::end();
            ConstIterator iter = BaseType::begin();
            ConstIterator end  = BaseType::end();

            for(; iter != end; ++iter)
            {
                if (predicate(*iter))
                {
                    result = iter;
                    break;
                }
            }

            return result;
        }

        template<typename PredicateType>
        Iterator findif(const PredicateType& predicate)
        {
            Iterator result = BaseType::end();
            Iterator iter = BaseType::begin();
            Iterator end  = BaseType::end();

            for(; iter != end; ++iter)
            {
                if (predicate(*iter))
                {
                    result = iter;
                    break;
                }
            }

            return result;
        }

        template<typename FuncType>
        Vector& sort(const FuncType& func)
        {
            std::sort(BaseType::begin(), BaseType::end(), func);
            return *this;
        }

        template<typename FuncType>
        void foreach(const FuncType& func)
        {
            Iterator iter = BaseType::begin();
            Iterator end  = BaseType::end();

            for(; iter != end; ++iter)
            {
                func(*iter);
            }
        }

        template<typename PredicateType>
        Vector where(const PredicateType& predicate) const
        {
            Vector result;

            ConstIterator iter = BaseType::begin();
            ConstIterator end  = BaseType::end();

            for(; iter != end; ++iter)
            {
                if (predicate(*iter))
                {
                    result.push_back(*iter);
                }
            }

            return result;
        }

        template<typename DstType, typename FuncType>
        Vector<DstType> select(const FuncType& func) const
        {
            Vector<DstType> result;

            ConstIterator iter = BaseType::begin();
            ConstIterator end  = BaseType::end();

            for(; iter != end; ++iter)
            {
                result.push_back(func(*iter));
            }
            
            return result;
        }

        template<typename ContainerType>
        Vector& concat(const ContainerType& other)
        {
            BaseType::insert(BaseType::end(), other.begin(), other.end());
            return *this;
        }

        Vector& shiftleft(const ValueType& value)
        {
            BaseType::push_back(value);
            BaseType::erase(BaseType::begin());
            return *this;
        }

        Vector& shiftright(const ValueType& value)
        {
            BaseType::insert(BaseType::begin(), value);
            BaseType::pop_back();
            return *this;
        }
    };
}

#endif // GXVECTOR_H__
