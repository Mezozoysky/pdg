#include <pdg/core/assert_internal.hpp>

#if defined(PDG_SYSTEM_WINDOWS)
#include <Windows.h>
#include <intrin.h>
#elif defined(PDG_SYSTEM_LINUX)
#include <signal.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#else
#error "Unsupported system"
#endif
#include <stdlib.h>

#include <fmt/format.h>


namespace pdg::core
{


bool isRunningUnderDebugger()
{
#if defined(PDG_SYSTEM_WINDOWS)
    return IsDebuggerPresent();
#elif defined(PDG_SYSTEM_LINUX)
    std::string line;
    std::ifstream file("/proc/self/status");
    while (std::getline(file, line))
    {
        std::istringstream strm(line);
        std::string tag, value;
        strm >> tag >> value;
        if (tag == "TracerPid:" && value != "0")
        {
            return true;
        }
    }
    return false;
#else
#error "Unsupported system"
#endif
}


void debugBreak()
{
#if defined(PDG_SYSTEM_WINDOWS)
    __debugbreak();
#elif defined(PDG_SYSTEM_LINUX)
    raise(SIGTRAP);
#else
#error "Unsupported system"
#endif
}


void assertInternal(char const * condition, char const * file, unsigned const line, char const * message)
{
    fmt::print("Assertion failure: {}\n\tcondition: {}\n\tfile: '{}', line: {}\n",
               message,
               condition,
               file, line);
    fflush(stdout);

    if (isRunningUnderDebugger())
    {
        debugBreak();
        return;
    }
    abort();
}


} // namespace pdg::core
