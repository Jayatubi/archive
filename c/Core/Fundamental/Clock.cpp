#include "Clock.h"
#include "Math.h"
#include <sys/time.h>

namespace GX
{
    U64 Clock::s_maxDelta = 0;
    U64 Clock::s_currentMilliseconds = 0;
    F32 Clock::s_globalTimeScale = 1;

    F32 Clock::toSeconds(U64 milliSeconds)
    {
        return milliSeconds * 1e-3;
    }

    U64 Clock::fromSeconds(F32 seconds)
    {
        return seconds * 1e3;
    }

    F32 Clock::currentSeconds()
    {
        return toSeconds(currentMilliseconds());
    }
    
    U64 Clock::currentMilliseconds()
    {
        return s_currentMilliseconds;
    }

    U64 Clock::currentRealMilliseconds()
    {
        timeval now;
        gettimeofday(&now,  0);
        return now.tv_sec * 1000 + now.tv_usec / 1000;
    }

    U64 Clock::getMaxDeltaMilliseconds()
    {
        return s_maxDelta;
    }

    void Clock::setMaxDeltaSeconds(F32 maxDelta)
    {
        s_maxDelta = fromSeconds(maxDelta);
    }

    void Clock::setMaxDeltaMilliseconds(U64 maxDelta)
    {
        s_maxDelta = maxDelta;
    }

    void Clock::globalTimeScale(GX::F32 scale)
    {
        s_globalTimeScale = scale;
    }

    const GX::F32& Clock::globalTimeScale()
    {
        return s_globalTimeScale;
    }
    
    void Clock::staticUpdate()
    {
        s_currentMilliseconds = currentRealMilliseconds();
    }

    Clock::Clock()
    : m_lastTick(0)
    , m_delta(0)
    , m_timeScale(1)
    , m_eplased(0)
    , m_eplasedNoScale(0)
    , m_offset(0)
    , m_ignoreGlobalScale(false)
    {
        m_lastTick = currentMilliseconds();
    }

    void Clock::update()
    {
        U64 now = currentMilliseconds();

        if (m_lastTick != 0)
        {
            m_delta = now - m_lastTick;
            if (s_maxDelta > 0)
            {
                m_delta = min(s_maxDelta, m_delta);
            }
            m_eplasedNoScale += m_delta;
            m_delta *= m_timeScale;
            if (!m_ignoreGlobalScale)
            {
                m_delta *= s_globalTimeScale;
            }
            m_eplased += m_delta;
        }

        m_lastTick = currentMilliseconds();
    }

    F32 Clock::deltaSeconds()
    {
        return toSeconds(deltaMilliseconds());
    }

    U64 Clock::deltaMilliseconds()
    {
        return m_delta;
    }

    F32 Clock::getTimeScale() const
    {
        return m_timeScale;
    }

    void Clock::setTimeScale(F32 timeScale)
    {
        m_timeScale = timeScale;
    }

    F32 Clock::getElapsedSeconds() const
    {
        return toSeconds(m_eplased + m_offset);
    }

    F32 Clock::getElapsedSecondsNoScale() const
    {
        return toSeconds(m_eplasedNoScale + m_offset);
    }

    U64 Clock::getElapsedMilliseconds() const
    {
        return m_eplased + m_offset;
    }

    U64 Clock::getElapsedMillisecondsNoScale() const
    {
        return m_eplasedNoScale + m_offset;
    }

    U64 Clock::getElpasedWithoutOffset() const
    {
        return m_eplased;
    }

    U64 Clock::getOffset() const
    {
        return m_offset;
    }

    void Clock::setOffsetSeconds(F32 offset)
    {
        m_offset = fromSeconds(offset);
    }

    void Clock::setOffsetMilliseconds(U64 offset)
    {
        m_offset = offset;
    }
    
    void Clock::setElapsedSeconds(F32 elapsed)
    {
        U64 ms = fromSeconds(elapsed);
        m_eplasedNoScale = ms;
        m_eplased = ms;
    }
    
    void Clock::setElapsedMilliseconds(U64 elapsed)
    {
        m_eplasedNoScale = elapsed;
        m_eplased = elapsed;
    }

    bool Clock::getIgnoreGlobalScale() const
    {
        return m_ignoreGlobalScale;
    }

    void Clock::setIgnoreGlobalScale(bool ignore)
    {
        m_ignoreGlobalScale = ignore;
    }

    tm * Clock::getTime()
    {
        struct tm *tm;
        time_t timep;

        struct cc_timeval now;
        CCTime::gettimeofdayCocos2d(&now, NULL);
        timep = now.tv_sec;
        tm = localtime(&timep);

        return tm;
//        int year = tm->tm_year + 1900;
//        int month = tm->tm_mon + 1;
//        int day = tm->tm_mday;
//        int hour=tm->tm_hour;
//        int min=tm->tm_min; 
//        int second=tm->tm_sec; 
    }
}