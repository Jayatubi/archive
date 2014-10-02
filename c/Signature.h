template<typename _R>
struct Signature<_R (*)()>
{
    typedef _R ResultType;
};
 
template<typename _R, typename _P1>
struct Signature<_R (*)(_P1)>
{
    typedef _R  ResultType;
    typedef _P1 ParamType1;
};
 
template<typename _R, typename _P1, typename _P2>
struct Signature<_R (*)(_P1, _P2)>
{
    typedef _R ResultType;
    typedef _P1 ParamType1;
    typedef _P2 ParamType2;
};
