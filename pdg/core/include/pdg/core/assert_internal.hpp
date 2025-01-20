#pragma once

#include <pdg/core/build_config.hpp>

#include "macros.hpp"


#ifdef PDG_ASSERTS_ENABLED

namespace pdg::core
{


void assertInternal(char const * condition, char const * file, unsigned const line, char const * message);


} // namspace pdg::core


#define PDG_ASSERT_INTERNAL(condition, message)                                 \
    do                                                                           \
    {                                                                            \
        if (!(condition))                                                        \
        {                                                                        \
            pdg::core::assertInternal(#condition, __FILE__, __LINE__, message); \
        }                                                                        \
    } while (false)

#else // PDG_ASSERTS_ENABLED

#define PDG_ASSERT_INTERNAL(...)

#endif // PDG_ASSERTS_ENABLED
