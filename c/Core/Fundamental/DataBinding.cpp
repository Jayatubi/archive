#include "DataBinding.h"

namespace GX
{
    DataBinding DataBinding::s_defaultDataBinding;
    
    DataBinding::DataBinding()
    {
    }

    DataBinding::~DataBinding()
    {
    }

    void DataBinding::setData(U32 key, Any&& data)
    {
        Context& context = m_container[key];
        context.m_data = std::move(data);
        context.trigger();
    }

    void DataBinding::setData(U32 key, const Any& data)
    {
        Context& context = m_container[key];
        context.m_data = data;
        context.trigger();
    }

    const Any* DataBinding::getData(U32 key)
    {
        auto iter = m_container.find(key);
        return iter != m_container.end() ? &iter->second.m_data : nullptr;
    }

    void DataBinding::createBinding(U32 key, const FuncType &func)
    {
        if (func)
        {
            Context& context = m_container[key];
            context.m_signal.connect(func);
            func(context.m_data);
        }
    }

    void DataBinding::deleteBinding(U32 key, const FuncType &func)
    {
        if (func)
        {
            auto iter = m_container.find(key);
            if (iter != m_container.end())
            {
                iter->second.m_signal.disconnect(func);
            }
        }
    }
    
    GX::U32 DataBinding::getDataCount()
    {
        return m_container.size();
    }

    DataBinding& DataBinding::defaultDataBinding()
    {
        return s_defaultDataBinding;
    }
}
