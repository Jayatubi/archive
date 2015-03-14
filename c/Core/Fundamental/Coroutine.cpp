#include "Coroutine.h"

namespace GX
{
    WaitForFrames::WaitForFrames(S32 frames)
    : m_frames(frames)
    {}

    void WaitForFrames::next()
    {
        m_frames--;
    }

    bool WaitForFrames::isComplete()
    {
        return m_frames <= 0;
    }

    void WaitForFrames::exit()
    {
        m_frames = 0;
    }

    WaitForSeconds::WaitForSeconds(F32 seconds, bool ignoreGlobalScale, F32 maxDeltaTime)
    : m_duration(seconds)
    {
        m_clock.setMaxDeltaSeconds(maxDeltaTime);
        m_clock.setIgnoreGlobalScale(ignoreGlobalScale);
    }

    void WaitForSeconds::next()
    {
        m_clock.update();
    }

    bool WaitForSeconds::isComplete()
    {
        return m_clock.getElapsedSeconds() >= m_duration;
    }

    void WaitForSeconds::exit()
    {
        m_duration = 0;
    }

    void CoroutineScheduler::update()
    {
        if (!m_coroPendingList.empty())
        {
            m_coroList.splice(m_coroList.end(), m_coroPendingList);
        }

        if (!m_coroList.empty())
        {
            auto iter = m_coroList.begin();
            auto end  = m_coroList.end();
            for(; iter != end;)
            {
                CoroutineType coro = *iter;
                if (coro->isComplete())
                {
                    iter = m_coroList.erase(iter);
                }
                else
                {
                    coro->next();
                    ++iter;
                }
            }
        }
    }

    CoroutineScheduler::CoroutineType CoroutineScheduler::start(const CoroutineType coro)
    {
        m_coroPendingList.push_back(coro);

        return coro;
    }

    void CoroutineScheduler::stop(CoroutineType coro)
    {
        coro->exit();
    }

    void CoroutineScheduler::stopAll()
    {
        m_coroList.foreach([](CoroutineType coro)
                           {
                               coro->exit();
                           });
        m_coroPendingList.clear();
    }
}