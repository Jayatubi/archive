#ifndef GX_SLOT_H
#define GX_SLOT_H

namespace GX
{
    template<typename ResultType, typename ... ArgTypes >
    class Signal
    {
    public:
        typedef Function<ResultType, ArgTypes ... > FuncType;

        void connect(const FuncType& func)
        {
            m_funcs.push_back(func);
        }

        void disconnect(const FuncType& func)
        {
            auto iter = m_funcs.find(func);
            if (iter != m_funcs.end())
            {
                iter->nullify();
            }
        }

        operator bool()
        {
            return !m_funcs.empty();
        }

        Signal& operator()(ArgTypes ... args)
        {
            auto iter = m_funcs.begin();
            for(; iter != m_funcs.end();)
            {
                FuncType func = *iter;
                if (func)
                {
                    func(args ... );
                    ++iter;
                }
                else
                {
                    iter = m_funcs.erase(iter);
                }
            }

            return *this;
        }

    private:
        List<FuncType> m_funcs;
    };
}

#endif