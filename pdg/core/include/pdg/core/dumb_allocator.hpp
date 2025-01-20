#pragma once

#include <pdg/core/build_config.hpp>

#include "allocator.hpp"
#include <cstddef>
#include <cstdint>
#include <utility>


namespace pdg::core
{


class DumbAllocator final : public Allocator
{
public:
    DumbAllocator() = default;
    virtual ~DumbAllocator() = default;

    virtual void init() override;

    [[nodiscard]] virtual void * allocate(std::size_t const size, std::size_t const alignment) override;
    virtual void deallocate(void * ptr) override;
};


} // namespace pdg::core
