#ifndef GX_FUNCTION_H
#define GX_FUNCTION_H

namespace GX
{
    template<typename FuncImplType, bool> struct CompareAdviser;

    template<typename FuncImplType>
    struct CompareAdviser<FuncImplType, true>
    {
        static bool compare(const FuncImplType* pLeft, const FuncImplType* pRight)
        {
            return pLeft->m_func == pRight->m_func;
        }
    };

    template<typename FuncImplType>
    struct CompareAdviser<FuncImplType, false>
    {
        static bool compare(const FuncImplType* pLeft, const FuncImplType* pRight)
        {
            return pLeft->m_unreliableHash == pRight->m_unreliableHash;
        }
    };

    template<typename ReturnType, typename ... ArgTypes>
    class FunctorImpl
    {
    public:
        GX_CLASSID_ROOT(0);
        virtual ~FunctorImpl() {}
        virtual ReturnType operator()(ArgTypes ... args) const = 0;
        virtual bool operator == (const FunctorImpl& right) const = 0;
    };

    template<typename FuncType, typename ReturnType, typename ... ArgTypes>
    class CompatibleFuncImpl : public FunctorImpl<ReturnType, ArgTypes ...>
    {
    public:
        GX_CLASSTAG("CompatibleFuncImpl");

        CompatibleFuncImpl(const FuncType& func)
        : m_func(func)
        , m_unreliableHash(reinterpret_cast<Size>(&func))
        {}

        virtual ReturnType operator() (ArgTypes ... args) const
        {
            return m_func(args ... );
        }

        typedef CompareAdviser<CompatibleFuncImpl, Meta::IsComparable<FuncType>::Result> TheCompareAdviser;

        friend TheCompareAdviser;

        virtual bool operator == (const FunctorImpl<ReturnType, ArgTypes ...>& right) const
        {
            const CompatibleFuncImpl* pRight = right.template as<CompatibleFuncImpl>();
            return (this == pRight) || (pRight != nullptr && TheCompareAdviser::compare(this, pRight));
        }

    private:
        FuncType m_func;
        Size m_unreliableHash;
    };

    template<typename ObjectType, typename FuncType, typename ReturnType, typename ... ArgTypes>
    class MemberFuncImpl : public FunctorImpl<ReturnType, ArgTypes ...>
    {
    public:
        GX_CLASSTAG("MemberFuncImpl");

        MemberFuncImpl(ObjectType* pObj, const FuncType& func)
        : m_pObj(pObj)
        , m_func(func)
        {}

        virtual ReturnType operator() (ArgTypes ... args) const
        {
            return (m_pObj->*m_func)(args ... );
        }

        virtual bool operator == (const FunctorImpl<ReturnType, ArgTypes ...>& right) const
        {
            const MemberFuncImpl* pRight = right.template as<MemberFuncImpl>();

            return pRight != nullptr && pRight->m_func == m_func && pRight->m_pObj == m_pObj;
        }

    private:
        ObjectType* m_pObj;
        FuncType m_func;
    };

    template<typename ReturnType, typename ... ArgTypes>
    class Function
    {
    public:

        typedef Tuple<ArgTypes ...> ArgType;

        Function()
        : m_pFunc(nullptr)
        {}

        Function(decltype(nullptr))
        : m_pFunc(nullptr)
        {}

        template<typename FuncType>
        Function(const FuncType& func)
        : m_pFunc(new CompatibleFuncImpl<FuncType, ReturnType, ArgTypes ...>(func))
        {}

        template<typename ObjectType, typename FuncType>
        Function(ObjectType& obj, const FuncType& func)
        : m_pFunc(new MemberFuncImpl<ObjectType, FuncType, ReturnType, ArgTypes ...>(&obj, func))
        {}

        ReturnType operator() (ArgTypes ... args) const
        {
            return m_pFunc != nullptr ? (*m_pFunc)(args ... ) : ReturnType();
        }

        bool operator == (const Function& right) const
        {
            bool result = false;

            if (m_pFunc == nullptr)
            {
                result = right.m_pFunc == nullptr;
            }
            else
            {
                result = right.m_pFunc != nullptr && *m_pFunc == *right.m_pFunc;
            }

            return result;
        }

        void nullify()
        {
            m_pFunc = nullptr;
        }

        operator bool() const
        {
            return m_pFunc != nullptr;
        }

    private:
        SmartPtr< FunctorImpl<ReturnType, ArgTypes ...> > m_pFunc;
    };

    template <typename ClassType, typename ReturnType, typename... ArgTypes>
    Function<ReturnType, ArgTypes ... > GetLambdaFuncType(ReturnType(ClassType::*)(ArgTypes...) const);

    template<typename LambdaType>
    auto Bind(const LambdaType& func)
    {
        typedef decltype(GetLambdaFuncType(&LambdaType::operator())) FuncType;
        return FuncType(func);
    }

    template<typename ReturnType, typename ... ArgTypes>
    auto Bind(ReturnType(* func)(ArgTypes ...))
    {
        return Function<ReturnType, ArgTypes ...>(func);
    }

    template<typename ObjectType, typename OwnerType, typename ReturnType, typename ... ArgTypes>
    auto Bind(ObjectType& obj, ReturnType(OwnerType::* func)(ArgTypes ...))
    {
        GX_STATIC_ASSERT((Meta::IsDerived<OwnerType, ObjectType>::Result), "Invalid bind type");
        return Function<ReturnType, ArgTypes ...>(obj, static_cast< ReturnType(ObjectType::*)(ArgTypes ...) >(func));
    }

    template<typename BindFuncType, typename ArgType, typename ReturnType = void>
    class UnaryProxyFunc : public FunctorImpl<ReturnType, ArgType>
    {
    public:
        typedef typename TupleAt<0, typename BindFuncType::ArgType>::ValueType      ConcreteType;
        typedef typename Meta::RemoveAll<ConcreteType>::Result                      RawConcreteType;

        UnaryProxyFunc(const BindFuncType& underlyingFunc)
        : m_underlyingFunc(underlyingFunc)
        {}

        virtual ReturnType operator()(ArgType arg) const
        {
            GX_STATIC_ASSERT((Meta::IsDerived<typename Meta::RemoveAll<ArgType>::Result, RawConcreteType>::Result), "Type dismatch");
            return m_underlyingFunc(static_cast<ConcreteType>(arg));
        }

        virtual bool operator == (const FunctorImpl<ReturnType, ArgType>& right) const
        {
            const UnaryProxyFunc* pProxy = right.template as<UnaryProxyFunc>();

            return pProxy != nullptr && m_underlyingFunc == pProxy->m_underlyingFunc;
        }

    private:
        BindFuncType m_underlyingFunc;
    };


}

#endif