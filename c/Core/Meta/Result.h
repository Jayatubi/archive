#ifndef GX_META_RESULT_H
#define GX_META_RESULT_H

/*
    This type defines for other meta classes.
 */

#include "TypeList.h"

namespace GX
{
    namespace Meta
    {
        namespace Details
        {
            typedef EmptyType _Yes[1];
            typedef EmptyType _No[2];
        }

        typedef Details::_Yes& Yes;
        typedef Details::_No&  No;   

        struct TrueType
        {
            enum
            {
                Result = 1
            };
        };

        struct FalseType
        {
            enum
            {
                Result = 0
            };
        };
    }
}

#endif