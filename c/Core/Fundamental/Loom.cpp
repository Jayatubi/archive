#include "Loom.h"
#include "Util.h"

namespace GX
{
    Loom::Loom()
    {
        resetThread();
    }

    Loom::~Loom()
    {
    }

    void Loom::query(const FuncType& func)
    {
        if (isOnThread())
        {
            func();
        }
        else
        {
            if (m_cirtical.lock(true))
            {
                m_funcList.connect(func);
                m_cirtical.unlock();
            }
        }
    }

    void Loom::processQueue()
    {
        GX_ASSERT(isOnThread(), "This method could only be execute on main thread");

        if (m_funcList && m_cirtical.lock())
        {
            m_funcList();
            reconstruct(m_funcList);
            m_cirtical.unlock();
        }
    }

    void Loom::resetThread()
    {
        m_thread = pthread_self();
    }

    bool Loom::isOnThread()
    {
        return pthread_self() == m_thread;
    }
}