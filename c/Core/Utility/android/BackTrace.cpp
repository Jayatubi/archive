#include "Framework/Core/Utility/BackTrace.h"
#include <dlfcn.h>
#include <ucontext.h>
#include <corkscrew/backtrace.h>
#include <backtrace-arch.h>

namespace GX
{    
    void dump_stack(int sig, siginfo_t* sig_info, void* ptr)
    {
        const size_t BACKTRACE_FRAMES_MAX = 0xFF;

        backtrace_frame_t frames[BACKTRACE_FRAMES_MAX];
        backtrace_symbol_t symbols[BACKTRACE_FRAMES_MAX];

        map_info_t* const info = acquire_my_map_info_list();
        const ssize_t size = unwind_backtrace_signal_arch(sig_info, ptr, info, frames, 0, BACKTRACE_FRAMES_MAX);
        get_backtrace_symbols(frames, size, symbols);

        for (int i = 0; i < size; i++)
        {
            backtrace_symbol_t& symbol = symbols[i];
            CCLOGERROR("#%02d  pc %08X  %s(%s+%08X)",
                        i,
                        symbol.relative_pc,
                        symbol.map_name ? symbol.map_name : "<unknown>",
                        symbol.demangled_name ? symbol.demangled_name : symbol.symbol_name,
                        symbol.relative_pc - symbol.relative_symbol_addr);
        }

        free_backtrace_symbols(symbols, size);
        release_my_map_info_list(info);
    }
}
