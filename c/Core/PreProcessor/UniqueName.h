#ifndef GX_PREPROCESSOR_UNIQUENAME_H
#define GX_PREPROCESSOR_UNIQUENAME_H

#include "Cat.h"

#define PP_UNIQUE_NAME( base ) PP_CAT( base, __LINE__ )

#endif // GX_PREPROCESSOR_UNIQUENAME_H
