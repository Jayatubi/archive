#ifndef GX_THREAD_H
#define GX_THREAD_H

#include <pthread.h>

namespace GX
{
    // 微秒
    static inline int sleep(int us)
    {
        struct timespec stReq;

        stReq.tv_sec    =    us/1000000;
        stReq.tv_nsec    =    (us % 1000000)*1000;

        return nanosleep(&stReq, NULL);
    }

    class CriticalSection
    {
    public:
        CriticalSection()
        {
            pthread_mutex_init(&m_critialSection, NULL);
        }

        ~CriticalSection()
        {
            pthread_mutex_destroy(&m_critialSection);
        }

        bool lock(bool block = false)
        {
            return (block ? pthread_mutex_lock(&m_critialSection) : pthread_mutex_trylock(&m_critialSection)) == 0;
        }

        void unlock()
        {
            pthread_mutex_unlock(&m_critialSection);
        }

    private:
        pthread_mutex_t m_critialSection;
    };
    
    
    struct CriticalSectionScopeLocker
    {
        CriticalSectionScopeLocker(CriticalSection &cs):m_cs(cs)
        {
            m_cs.lock(true);
        }
        
        ~CriticalSectionScopeLocker()
        {
            m_cs.unlock();
        }
        
        CriticalSection &m_cs;
    };
    

    typedef void* (*ThreadFunction)(void* data);
    class Thread
    {
    public:
        Thread()
        :m_thread(0)
        {}

        ~Thread()
        {
            join();
        }

        bool create(ThreadFunction runFunc, void* paramData)
        {
            assert(!m_thread);
            pthread_create(&m_thread, NULL, runFunc, paramData);
            return true;
        }
        
        void join()
        {
            if(m_thread != 0)
            {
                pthread_join(m_thread, 0);
                m_thread = 0;
            }            
        }
        
    protected:
        pthread_t m_thread;
    };
    
    
    class WorkThread : public Thread
    {
    public:
        
        typedef std::function<void ()> tWorkFunc;
        
        bool create()
        {
            assert(!m_thread);
            pthread_create(&m_thread, NULL, WorkThreadFunction, this);
            return true;
        }
        
        static void *WorkThreadFunction(void *p)
        {
            WorkThread *pThis = reinterpret_cast<WorkThread*>(p);
            return pThis->run();
        }
        
        virtual void *run() = 0;
        

    protected:
        tWorkFunc m_workFunc;
        
    };
    
}

#endif // GX_THREAD_H
