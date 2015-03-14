#include "../PreProcessor/Repeat.h"
#include "../PreProcessor/If.h"
#include "../PreProcessor/CAT.h"

#define SIGNATURE_TEMPLATE_ARGS(_, i)   , typename _P##i
#define SIGNATRUE_FUNCTION_ARGS(_, i)   PP_COMMA_IF(i) _P##i
#define SIGNATRUE_TYPEDEF(_, i)         typedef _P##i ParamType##i; 
#define SIGNATURE_TYPELIST_NAME(n)      PP_CAT(TypeList_, n)

template<typename _R PP_REPEAT(SIGNATURE_ARG_COUNT, SIGNATURE_TEMPLATE_ARGS, _)>
struct Signature<_R(*)(PP_REPEAT(SIGNATURE_ARG_COUNT, SIGNATRUE_FUNCTION_ARGS, _))>
{
    typedef _R ResultType;
    PP_REPEAT(SIGNATURE_ARG_COUNT, SIGNATRUE_TYPEDEF, _)
#if SIGNATURE_ARG_COUNT == 0
    typedef TypeList_0 ParamList;
#else
    typedef SIGNATURE_TYPELIST_NAME(SIGNATURE_ARG_COUNT)<PP_REPEAT(SIGNATURE_ARG_COUNT, SIGNATRUE_FUNCTION_ARGS, _)> ParamList;
#endif
    enum { ParamCount = SIGNATURE_ARG_COUNT };
};

#undef SIGNATURE_TEMPLATE_ARGS
#undef SIGNATRUE_FUNCTION_ARGS
#undef SIGNATRUE_TYPEDEF
#undef SIGNATURE_TYPELIST_NAME