#pragma once

#include <pdg/core/build_config.hpp>

#include <cstdint>
#include <cstddef>


namespace pdg::core
{


std::uintptr_t calcAdjustment(std::uintptr_t const addr, std::size_t const alignment);
std::uintptr_t calcAdjustment(std::uintptr_t const addr,
                              std::size_t const alignment,
                              std::size_t const headerSize);


} // namespace pdg::core
