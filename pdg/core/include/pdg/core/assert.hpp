#pragma once

#include <pdg/core/build_config.hpp>

#include "macros.hpp"


#ifdef PDG_ASSERTS_ENABLED

#include "assert_internal.hpp"
#define PDG_ASSERT PDG_ASSERT_INTERNAL

#else // PDG_ASSERTS_ENABLED

#define PDG_ASSERT(...)

#endif // PDG_ASSERTS_ENABLED

namespace pdg::code
{
} // namespace pdg::code
