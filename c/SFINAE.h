template<typename ClassType>
struct HasToStringFunction
{
    typedef struct { char[2]; } Yes;
    typedef struct { char[1]; } No;
     
    template<typename FooType, char* (FooType::*)()>
    struct FuncMatcher;
 
    template<typename FooType>
    static Yes Tester(FuncMatcher<FooType, &FooType::ToString>*);
 
    template<typename FooType>
    static No Tester(...);
 
    enum
    {
        Result = sizeof(Tester<ClassType>(nullptr)) == sizeof(Yes)
    };
};

template<typename ClassType>
struct HasSuper
{
    typedef struct { char[2]; } Yes;
    typedef struct { char[1]; } No;
     
    template<typename FooType>
    struct FuncMatcher;
 
    template<typename FooType>
    static Yes Tester(FuncMatcher<typename FooType::Super>*);
 
    template<typename FooType>
    static No Tester(...);
 
    enum
    {
        Result = sizeof(Tester<ClassType>(nullptr)) == sizeof(Yes)
    };
};
