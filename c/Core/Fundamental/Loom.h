#ifndef GX_LOOM_H
#define GX_LOOM_H

namespace GX
{
    class Loom : public Singleton<Loom>
    {
    public:
        typedef Signal<void> FuncList;
        typedef typename FuncList::FuncType FuncType;

        Loom();
        ~Loom();

        void query(const FuncType& func);
        void processQueue();
        void resetThread();
    private:
        bool isOnThread();

    private:
        FuncList m_funcList;

        pthread_t m_thread;
        CriticalSection m_cirtical;
    };
}

#endif