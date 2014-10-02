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
        Result = sizeof(Tester<ClassType>(NULL)) == sizeof(Yes)
    };
};
 
bool a_has_tostring = HasToStringFunction<A>::Result;   // True
bool b_has_tostring = HasToStringFunction<B>::Result;   // False
