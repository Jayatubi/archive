#ifndef GX_META_IFTHENELSE_H
#define GX_META_IFTHENELSE_H

/*
    This meta classes are used to determine a value or type according to a boolean condition

    Example:

        Meta::IfThenElse
        <
            sizeof(char) == sizeof(long),
            int,
            long
        >::Result                               // Reulst is: long

        Meta::IfThenElseValue
        <
            sizeof(char) == sizeof(char),
            0,
            1
        >::Result                               // Reulst is: 0
*/

namespace GX
{
    namespace Meta
    {
        template<bool cond, typename Then, typename Else>
        struct IfThenElse
        {
            typedef Else Result;
        };

        template<typename Then, typename Else>
        struct IfThenElse<true, Then, Else>
        {
            typedef Then Result;
        };

        template<bool cond, int Then, int Else>
        struct IfThenElseValue
        {
            enum { Result = Else };
        };

        template<int Then, int Else>
        struct IfThenElseValue<true, Then, Else>
        {
            enum { Result = Then };
        };
    }
}

#endif