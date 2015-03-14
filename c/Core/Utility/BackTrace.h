#ifndef GX_BACKTRACE_H
#define GX_BACKTRACE_H

#include <signal.h>

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <dlfcn.h>
#include <ucontext.h>
#endif

namespace GX
{
    void dump_stack(int sig, siginfo_t* sig_info, void* ptr);
}


#endif