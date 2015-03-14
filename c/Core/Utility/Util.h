#ifndef GX_UTIL_H
#define GX_UTIL_H

namespace GX
{
    template<typename ValueType>
    void zeroMemory(ValueType& data)
    {
        GX_STATIC_ASSERT(Meta::IsPOD<ValueType>::Result, "Call ZeroMemory on non-pod type");
        memset(&data, 0, sizeof(ValueType));
    }

    template<typename ValueType, int N, int M>
    void copyArray(ValueType (&dst)[N], const ValueType (&src)[M])
    {
        GX_STATIC_ASSERT(Meta::IsPOD<ValueType>::Result, "Call CopyArray on non-pod type");
        memcpy(dst, src, Meta::Min<N, M>::Result * sizeof(ValueType));
    }

    template<typename ValueType>
    void copyMemory(ValueType& dst, const ValueType& src)
    {
        GX_STATIC_ASSERT(Meta::IsPOD<ValueType>::Result, "Call CopyMemory on non-pod type");
        memcpy(&dst, &src, sizeof(ValueType));
    }

    namespace Details
    {
        template<typename ContainerType, bool>
        struct deepClearImpl
        {
            static void clearVector(ContainerType& container)
            {
                container.clear();
            }
            static void clearMap(ContainerType& container)
            {
                container.clear();
            }
        };

        template<typename ContainerType>
        struct deepClearImpl<ContainerType, true>
        {
            static void clearVector(ContainerType& container)
            {
                typename ContainerType::iterator iter = container.begin();
                typename ContainerType::iterator end  = container.end();

                for(; iter != end; ++iter)
                {
                    CC_SAFE_DELETE(*iter);
                }
                container.clear();
            }

            static void clearMap(ContainerType& container)
            {
                typename ContainerType::iterator iter = container.begin();
                typename ContainerType::iterator end  = container.end();

                for(; iter != end; ++iter)
                {
                    CC_SAFE_DELETE(iter->second);
                }
                container.clear();
            }
        };
    }

    template<typename ValueType>
    void deepClear(GX::Vector<ValueType>& container)
    {
        Details::deepClearImpl<GX::Vector<ValueType>, Meta::IsPtr<ValueType>::Result>::clearVector(container);
    }

    template<typename KeyType, typename ValueType>
    void deepClear(GX::Map<KeyType, ValueType>& container)
    {
        Details::deepClearImpl<GX::Map<KeyType, ValueType>, Meta::IsPtr<ValueType>::Result>::clearMap(container);
    }

    namespace Details
    {
        template<typename SrcType>
        class AutoCastProxy
        {
        public:
            inline AutoCastProxy(const SrcType& value)
            : m_value(value)
            {}

            inline AutoCastProxy(const AutoCastProxy& right)
            : m_value(right.m_value)
            {}

            template<typename DstType>
            inline operator DstType()
            {
                return static_cast<DstType>(m_value);
            }
        private:
            const SrcType& m_value;
        };
    }

    template<typename ValueType>
    Details::AutoCastProxy<ValueType> AutoCast(const ValueType& value)
    {
        GX_STATIC_ASSERT(Meta::IsPOD<ValueType>::Result, "Call AutoCast on non-pod type");
        return Details::AutoCastProxy<ValueType>(value);
    }

    template<typename ValueType, typename ... ArgTypes>
    void reconstruct(ValueType& value, ArgTypes ... args)
    {
        value.~ValueType();
        new (&value) ValueType(args ... );
    }

    template<typename ValueType>
    void wildAssign(void* dst, const ValueType& value)
    {
        GX_ASSERT(dst != nullptr, "Invalid address");

        memcpy(dst, &value, sizeof(ValueType));
    }
}


#endif
