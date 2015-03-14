#ifndef CLOCK_H
#define CLOCK_H

namespace GX
{
    class Clock
    {
    public:
        Clock();

        static tm * getTime();

        static F32 currentSeconds();
        static U64 currentMilliseconds();
        static U64 currentRealMilliseconds();

        static F32 toSeconds(U64 milliSeconds);
        static U64 fromSeconds(F32 seconds);

        static U64 getMaxDeltaMilliseconds();
        static void setMaxDeltaSeconds(F32 maxDelta);
        static void setMaxDeltaMilliseconds(U64 maxDelta);

        static void staticUpdate();
        
        void update();
        
        F32 deltaSeconds();
        U64 deltaMilliseconds();

        F32 getTimeScale() const;
        void setTimeScale(F32 timeScale);

        F32 getElapsedSeconds() const;
        F32 getElapsedSecondsNoScale() const;

        U64 getElapsedMilliseconds() const;
        U64 getElapsedMillisecondsNoScale() const;

        U64 getElpasedWithoutOffset() const;

        U64 getOffset() const;
        void setOffsetSeconds(F32 offset);
        void setOffsetMilliseconds(U64 offset);
        void setElapsedSeconds(F32 elapsed);
        void setElapsedMilliseconds(U64 elapsed);

        bool getIgnoreGlobalScale() const;
        void setIgnoreGlobalScale(bool ignore);

        static void globalTimeScale(GX::F32 scale);
        static const GX::F32& globalTimeScale();

    private:
        U64 m_lastTick;
        U64 m_delta;
        U64 m_eplased;
        U64 m_eplasedNoScale;
        U64 m_offset;
        F32 m_timeScale;
        bool m_ignoreGlobalScale;

        static U64 s_maxDelta;
        static U64 s_currentMilliseconds;
        static F32 s_globalTimeScale;
    };
}

#endif