#ifndef GX_PREPROCESSOR_CAT_H_
#define GX_PREPROCESSOR_CAT_H_

#define PP_LEFT_BRACKET (
#define PP_RIGHT_BRACKET )

#define __PP_CAT_IMPL(a, b) a ## b

#define PP_CAT(a, b) __PP_CAT_IMPL(a, b)

#endif