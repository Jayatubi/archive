#include "Event.h"

namespace GX
{
    EventRouter::TicketType EventRouter::addListener(U32 eventId, const FuncType &func)
    {
        m_router[eventId].connect(func);
        return TicketType(eventId, func);
    }

    EventRouter::TicketType EventRouter::removeListener(U32 eventId, const FuncType &func)
    {
        m_router[eventId].disconnect(func);
        return TicketType(eventId, func);
    }

    void EventRouter::broadcast(const GX::EventBase &event)
    {
        m_router[event.getClassId()](event);
    }
}