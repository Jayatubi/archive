#ifndef GX_ASSERT_H
#define GX_ASSERT_H

#include <cstdlib>

#define GX_STATIC_ASSERT(expr, msg) static_assert( (expr), msg )
#define GX_FATAL(format, ...) do { cocos2d::CCLog(format, ##__VA_ARGS__); std::abort(); } while(0)

#ifdef NDEBUG
    #define GX_ASSERT(expr, format, ...) do { if (!(expr)) { cocos2d::CCLog(format, ##__VA_ARGS__); } } while(0)
#else
    #define GX_ASSERT(expr, format, ...) do { if (!(expr)) { cocos2d::CCLog(format, ##__VA_ARGS__); std::abort(); } } while(0)
#endif

#endif // GX_ASSERT_H
