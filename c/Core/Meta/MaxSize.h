#ifndef GX_MAXSIZE_H
#define GX_MAXSIZE_H

namespace GX
{
    namespace Meta
    {
        template<typename FisrtType, typename ... RestTypes>
        struct MaxSize
        {
            enum 
            {
                Result = Max<sizeof(FisrtType), MaxSize<RestTypes ...>::Result>::Result
            };
        };

        template<typename FirstType>
        struct MaxSize<FirstType>
        {
            enum
            {
                Result = sizeof(FirstType)
            };
        };
    }
}

#endif // GX_MAXSIZE_H
