#ifndef GX_COROUTINE_H
#define GX_COROUTINE_H

namespace GX
{
    class IEnumerable
    {
    public:
        IEnumerable() {};
        virtual ~IEnumerable() {};
        virtual void next() {};
        virtual bool isComplete() { return true; };
        virtual void exit() {};
        virtual bool move()
        {
            next();
            return !isComplete();
        }

        typedef SmartPtr<IEnumerable> PtrType;

        class AutoPtrType
        {
        public:
            AutoPtrType()
            {}
            
            AutoPtrType(PtrType ptr)
            : m_ptr(ptr)
            {}

            ~AutoPtrType()
            {
                release();
            }

            AutoPtrType& operator = (PtrType ptr)
            {
                if (m_ptr != ptr)
                {
                    release();
                    m_ptr = ptr;
                }

                return *this;
            }

            bool operator == (const PtrType& ptr)
            {
                return m_ptr == ptr;
            }

            bool operator != (const PtrType& ptr)
            {
                return m_ptr != ptr;
            }

            PtrType operator -> ()
            {
                return m_ptr;
            }

            void release()
            {
                if (m_ptr != nullptr)
                {
                    m_ptr->exit();
                }
            }

        private:
            PtrType m_ptr;
        };
    };

    class WaitForFrames : public IEnumerable
    {
    public:
        WaitForFrames(S32 frames);
        virtual void next();
        virtual bool isComplete();
        virtual void exit();

    private:
        S32 m_frames;
    };

    class WaitForSeconds : public IEnumerable
    {
    public:
        WaitForSeconds(F32 seconds, bool ignoreGlobalScale = true, F32 maxDeltaTime = 0);
        virtual void next();
        virtual bool isComplete();
        virtual void exit();

    private:
        F32             m_duration;
        Clock           m_clock;
    };

    class CoroutineScheduler : public Singleton<CoroutineScheduler>
    {
    public:
        typedef IEnumerable::PtrType      CoroutineType;
        typedef List<CoroutineType>       CoroutineListType;

        void update();

        CoroutineType start(const CoroutineType coro);

        void stop(CoroutineType coro);
        void stopAll();
        
    private:
        CoroutineListType m_coroList;
        CoroutineListType m_coroPendingList;
    };


    template<typename ... VairableTypes>
    class Context
    {
    public:
        typedef Tuple< VairableTypes ... > VairableType;

        Context(VairableTypes ... variable)
        : m_state(0)
        , m_variable(variable ...)
        {}

        operator S32()
        {
            return m_state;
        }

        Context& operator=(S32 state)
        {
            m_state = state;
            return *this;
        }

        operator IEnumerable::PtrType()
        {
            return m_subcoro;
        }

        Context& operator=(IEnumerable::PtrType subcoro)
        {
            m_subcoro = subcoro;
            return *this;
        }

        void reset()
        {
            m_state = 0;
            stop_subcoro();
        }

        void stop_subcoro()
        {
            if (m_subcoro != nullptr)
            {
                m_subcoro->exit();
                m_subcoro = nullptr;
            }
        }

        void exit()
        {
            m_state = -1;
            stop_subcoro();
        }

        template<U32 Index>
        typename TupleAt< Index, VairableType >::ValueType& variable()
        {
            return getTuple<Index>(m_variable);
        }

    private:
        S32 m_state;
        IEnumerable::PtrType m_subcoro;
        VairableType m_variable;
    };

    template<typename ReturnType = void, typename ... VairableTypes>
    class Coroutine : public IEnumerable
    {
    public:
        typedef Context<VairableTypes ... >             ContextType;
        typedef Function<ReturnType, ContextType&>      FuncType;

        Coroutine()
        {
        }

        Coroutine(const FuncType& func, VairableTypes ... vairable)
        : m_func(func)
        , m_context(vairable ... )
        {
        }

        virtual ReturnType next()
        {
            return m_func(m_context);
        }

        void exit()
        {
            m_context.exit();
        }

        virtual bool isComplete()
        {
            return m_context == -1;
        }
        
        void reenter()
        {
            m_context.reset();
        }

    private:
        ContextType m_context;
        FuncType m_func;
    };

    template<typename ReturnType = void, typename ... VairableTypes>
    IEnumerable::PtrType MakeCoroutine(
                                       const typename Coroutine<ReturnType, VairableTypes ... >::FuncType& func,
                                       VairableTypes ... variable)
    {
        return new Coroutine<ReturnType, VairableTypes ... >(func, variable ... );
    }

    namespace Details
    {
        template<typename ... VairableTypes>
        Context<VairableTypes ... > GetContextType(VairableTypes ...);
    }
}

#define coro_begin_impl(...) \
    GX::MakeCoroutine([=]( decltype(GX::Details::GetContextType(__VA_ARGS__))& context) \
    { \
        switch(context) \
        { \
            default: break; \
            bail: break; \
            case -1: break; \
            case 0: \

#define coro_begin coro_begin_impl()

#define coro_end_impl(...) \
            context = -1; \
        } \
    } __VA_ARGS__)

#define coro_end coro_end_impl()


#define coro_lines(...) __VA_ARGS__
#define coro_arg(Index) context.variable<Index>()
#define coro_start_impl(coro_instance)  GX::CoroutineScheduler::getInstance()->start(coro_instance)

#define coro(...) \
        coro_begin_impl() \
            __VA_ARGS__ \
        coro_end_impl()

#define coro_ex(variable, code) \
        coro_begin_impl(variable) \
            code \
        coro_end_impl( PP_COMMA variable)

#define coro_start(...)                 coro_start_impl(coro( __VA_ARGS__ ))
#define coro_start_ex(variable, code)   coro_start_impl(coro_ex( coro_lines(variable), coro_lines(code) ))
        
#define yield \
                if ((context = __LINE__) == 0) \
                { \
                    case __LINE__: ; \
                } \
                else \
                    for(bool ex = false;; ex = !ex) \
                        if (ex) goto bail; \
                        else

#define yield_wait(...) while(__VA_ARGS__) yield

#define yield_coroutine(...) \
                context = coro_start_impl(__VA_ARGS__); \
                while(!static_cast<GX::CoroutineScheduler::CoroutineType>(context)->isComplete()) \
                    yield


#endif
