#ifndef GX_METATYPELIST_H
#define GX_METATYPELIST_H

#include "../PreProcessor/Arg.h"
#include "../PreProcessor/Repeat.h"
#include "../PreProcessor/Cat.h"
#include "../PreProcessor/If.h"

/*
    This meta class is used for other meta classes. It could compress variant count of types into a single type.
 */

#define GX_TYPELIST_1(_T1) GX::Meta::TypeList<_T1, GX::Meta::EmptyType>
#define GX_TYPELIST_2(_T1, _T2) GX::Meta::TypeList<_T1, GX_TYPELIST_1(_T2)>
#define GX_TYPELIST_3(_T1, _T2, _T3) GX::Meta::TypeList<_T1, GX_TYPELIST_2(_T2, _T3)>
#define GX_TYPELIST_4(_T1, _T2, _T3, _T4) GX::Meta::TypeList<_T1, GX_TYPELIST_3(_T2, _T3, _T4)>
#define GX_TYPELIST_5(_T1, _T2, _T3, _T4, _T5) GX::Meta::TypeList<_T1, GX_TYPELIST_4(_T2, _T3, _T4, _T5)>
#define GX_TYPELIST_6(_T1, _T2, _T3, _T4, _T5, _T6) GX::Meta::TypeList<_T1, GX_TYPELIST_5(_T2, _T3, _T4, _T5, _T6)>
#define GX_TYPELIST_7(_T1, _T2, _T3, _T4, _T5, _T6, _T7) GX::Meta::TypeList<_T1, GX_TYPELIST_6(_T2, _T3, _T4, _T5, _T6, _T7)>
#define GX_TYPELIST_8(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8) GX::Meta::TypeList<_T1, GX_TYPELIST_7(_T2, _T3, _T4, _T5, _T6, _T7, _T8)>
#define GX_TYPELIST_9(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9) GX::Meta::TypeList<_T1, GX_TYPELIST_8(_T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9)>
#define GX_TYPELIST_10(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10) GX::Meta::TypeList<_T1, GX_TYPELIST_9(_T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10)>

#define GX_TYPELIST_ARG_AT(args, i) PP_COMMA_IF(i) PP_ARG_AT(i, args)
#define GX_TYPELIST(...) PP_CAT(GX_TYPELIST_, PP_ARG_COUNT(__VA_ARGS__)) PP_LEFT_BRACKET PP_REPEAT(PP_ARG_COUNT(__VA_ARGS__), GX_TYPELIST_ARG_AT, __VA_ARGS__) PP_RIGHT_BRACKET

namespace GX
{
    namespace Meta
    {
        struct EmptyType {};

        template<typename _P1, typename _P2>
        struct TypeList
        {
            typedef _P1 Head;
            typedef _P2 Tail;
        };

        struct TypeList_0 : public EmptyType {};

        template<typename _P1>
        struct TypeList_1 : public GX_TYPELIST_1(_P1) {};

        template<typename _P1, typename _P2>
        struct TypeList_2 : public GX_TYPELIST_2(_P1, _P2) {};

        template<typename _P1, typename _P2, typename _P3>
        struct TypeList_3 : public GX_TYPELIST_3(_P1, _P2, _P3) {};

        template<typename _P1, typename _P2, typename _P3, typename _P4>
        struct TypeList_4 : public GX_TYPELIST_4(_P1, _P2, _P3, _P4) {};

        template<typename _P1, typename _P2, typename _P3, typename _P4, typename _P5>
        struct TypeList_5 : public GX_TYPELIST_5(_P1, _P2, _P3, _P4, _P5) {};

        template<typename _P1, typename _P2, typename _P3, typename _P4, typename _P5, typename _P6>
        struct TypeList_6 : public GX_TYPELIST_6(_P1, _P2, _P3, _P4, _P5, _P6) {};

        template<typename _P1, typename _P2, typename _P3, typename _P4, typename _P5, typename _P6, typename _P7>
        struct TypeList_7 : public GX_TYPELIST_7(_P1, _P2, _P3, _P4, _P5, _P6, _P7) {};

        template<typename _P1, typename _P2, typename _P3, typename _P4, typename _P5, typename _P6, typename _P7, typename _P8>
        struct TypeList_8 : public GX_TYPELIST_8(_P1, _P2, _P3, _P4, _P5, _P6, _P7, _P8) {};

        template<typename _P1, typename _P2, typename _P3, typename _P4, typename _P5, typename _P6, typename _P7, typename _P8, typename _P9>
        struct TypeList_9 : public GX_TYPELIST_9(_P1, _P2, _P3, _P4, _P5, _P6, _P7, _P8, _P9) {};

        template<typename _P1, typename _P2, typename _P3, typename _P4, typename _P5, typename _P6, typename _P7, typename _P8, typename _P9, typename _P10>
        struct TypeList_10 : public GX_TYPELIST_10(_P1, _P2, _P3, _P4, _P5, _P6, _P7, _P8, _P9, _P10) {};
    }
}

#endif