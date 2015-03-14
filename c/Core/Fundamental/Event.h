#ifndef GX_EVENT_H
#define GX_EVENT_H

namespace GX
{
    class EventBase
    {
    public:
        GX_CLASSID_ROOT(0);
    };

    class EventRouter : public Singleton<EventRouter>
    {
    public:
        typedef GX::Signal<void, const EventBase&>  SignalType;
        typedef typename SignalType::FuncType       FuncType;
        typedef GX::Map<U32, SignalType>            RouterType;
        typedef std::pair<U32, FuncType>            TicketType;

        TicketType addListener(U32 eventId, const FuncType& func);

        template<typename EventType>
        inline TicketType addListener(const FuncType& func)
        {
            return addListener(EventType::CLASS_ID, func);
        }

        template<typename BindFuncType>
        inline TicketType addListenerAuto(const BindFuncType& func)
        {
            typedef UnaryProxyFunc<BindFuncType, const EventBase&> ProxyFuncType;
            return addListener<typename ProxyFuncType::RawConcreteType>(ProxyFuncType(func));
        }

        TicketType removeListener(U32 eventId, const FuncType& func);

        template<typename EventType>
        inline TicketType removeListener(const FuncType& func)
        {
            return removeListener(EventType::CLASS_ID, func);
        }

        template<typename BindFuncType>
        inline TicketType removeListenerAuto(const BindFuncType& func)
        {
            typedef UnaryProxyFunc<BindFuncType, const EventBase&> ProxyFuncType;
            return removeListener<typename ProxyFuncType::RawConcreteType>(ProxyFuncType(func));
        }

        void removeListeners(const FuncType& func)
        {
            m_router.foreachValue([&](SignalType& signal) { signal.disconnect(func); } );
        }

        void broadcast(const EventBase& event);

        template<typename EventType, typename ... ArgTyps>
        void broadcast(ArgTyps ... args)
        {
            if (m_router.contains(EventType::CLASS_ID))
            {
                broadcast(EventType(args ... ));
            }
        }
    private:
        RouterType m_router;
    };
}

/*
#define ADD_EVENT_LISTENER(EventType, Func)     GX::EventRouter::getInstance()->addListener<EventType>(Func)
#define ADD_EVENT_LISTENER_AUTO(Func)           GX::EventRouter::getInstance()->addListenerAuto(Func)

#define REMOVE_EVENT_LISTENER(EventType, Func)  GX::EventRouter::getInstance()->removeListener<EventType>(Func)
#define REMOVE_EVENT_LISTENER_AUTO(Func)        GX::EventRouter::getInstance()->removeListenerAuto(Func)

#define REMOVE_EVENT_LISTENER_ALL(Func)         GX::EventRouter::getInstance()->removeListeners(Func)
*/
#define BROADCAST_EVENT(Event)                  GX::EventRouter::getInstance()->broadcast(Event)
#define BROADCAST_EVENT_EX(Event, ...)          GX::EventRouter::getInstance()->broadcast<Event>(__VA_ARGS__)

#endif