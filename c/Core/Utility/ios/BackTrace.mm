#include "Framework/Core/Utility/BackTrace.h"
#include <execinfo.h>

namespace GX
{
    void dump_stack(int sig, siginfo_t* sig_info, void* ptr)
    {
        const size_t BACKTRACE_FRAMES_MAX = 0xFF;
        void* frames[BACKTRACE_FRAMES_MAX] = {0};
        size_t size = backtrace(frames, BACKTRACE_FRAMES_MAX);
        backtrace_symbols_fd(frames, size, STDERR_FILENO);
    }
}
