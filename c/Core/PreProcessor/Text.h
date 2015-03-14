#ifndef GX_PREPROCESSOR_TEXT_H
#define GX_PREPROCESSOR_TEXT_H

#define GX_PP_TEXT_IMPL(exp) #exp

#define GX_PP_TEXT( exp ) GX_PP_TEXT_IMPL(exp)

#endif // GX_PREPROCESSOR_TEXT_H
