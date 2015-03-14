#ifndef GX_DATABINDING_H__
#define GX_DATABINDING_H__

namespace GX
{
    class DataBinding
    {
    public:
        struct Context
        {
            typedef Signal<void, const Any&> SignalType;
            SignalType m_signal;
            Any m_data;

            void trigger()
            {
                m_signal(m_data);
            }
        };

        typedef Context::SignalType::FuncType   FuncType;
        typedef Map<U32, Context>               ContainerType;

        DataBinding();
        ~DataBinding();

        template<typename ValueType>
        void setData(U32 key, const ValueType& value)
        {
            setData(key, std::move(Any(value)));
        }

        void setData(U32 key, Any&& data);
        void setData(U32 key, const Any& data);
        const Any* getData(U32 key);
        void createBinding(U32 key, const FuncType& func);
        void deleteBinding(U32 key, const FuncType& func);
        GX::U32 getDataCount();

        static DataBinding& defaultDataBinding();

    private:
        ContainerType m_container;

        static DataBinding s_defaultDataBinding;
    };
}

#endif