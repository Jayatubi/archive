#ifndef GX_PREPROCESSOR_JOIN_H
#define GX_PREPROCESSOR_JOIN_H

#include "Arg.h"
#include "If.h"
#include "Repeat.h"

#define PP_JOIN_IMPL(Args, i)       PP_COMMA_IF(i) PP_ARG_AT(i, Args)
#define PP_JOIN(...)                PP_REPEAT( PP_ARG_COUNT(__VA_ARGS__), PP_JOIN_IMPL, (__VA_ARGS__) )

#endif
