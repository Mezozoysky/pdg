#include <pdg/core/allocator_utils.hpp>


namespace pdg::core
{


std::uintptr_t calcAdjustment(std::uintptr_t const addr, std::size_t const alignment)
{
    std::size_t const factor = (addr / alignment) + 1u;
    std::uintptr_t const alignedAddr = alignment * factor;
    return (alignedAddr - addr);
}


std::uintptr_t calcAdjustment(std::uintptr_t const addr, std::size_t const alignment, std::size_t const headerSize)
{
    std::size_t adjustment = calcAdjustment(addr, alignment);

    if (adjustment < headerSize)
    {
        std::size_t const shortage = headerSize - adjustment;
        std::size_t factor = (shortage / alignment);
        if (shortage % alignment > 0u)
        {
            factor += 1u;
        }
        adjustment += alignment * factor;
    }

    return adjustment;
}


} // namespace pdg::core

