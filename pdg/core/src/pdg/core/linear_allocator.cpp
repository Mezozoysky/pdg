#include <pdg/core/linear_allocator.hpp>
#include <pdg/core/allocator_utils.hpp>
#include <pdg/core/assert.hpp>

#include <cstdint>
#include <cstdlib>

#include <iostream>


namespace pdg::core
{


//std::uintptr_t getAlignMiss(std::size_t alignOf, void const * const ptr)
//{
//    return (std::uintptr_t)(ptr) & (alignOf - 1u);
//}
//
//
//std::uintptr_t getAlignAdjustment(std::size_t alignOf, void const * const ptr)
//{
//    auto const miss = getAlignMiss(alignOf, ptr);
//
//    if (miss == 0u)
//    {
//        return 0u;
//    }
//
//    return (alignOf - miss);
//}
//
//
//void * alignMemory(std::size_t alignOf, std::size_t size, void * bufferStart, std::size_t bufferSize)
//{
//    assert(alignOf != 0u);
//
//    std::uintptr_t adjustment = getAlignAdjustment(alignOf, bufferStart);
//    if (bufferSize < adjustment || bufferSize - adjustment < size)
//    {
//        // TODO: log error
//        return nullptr;
//    }
//
//    bufferStart = (void *)((std::uintptr_t)bufferStart + adjustment);
//    return bufferStart;
//}


LinearAllocator::LinearAllocator()
: mBuffer(nullptr)
, mBufferSize(0u)
, mOffset(0u)
{
}


LinearAllocator::LinearAllocator(std::size_t bufferSize)
: mBuffer(nullptr)
, mBufferSize(bufferSize)
, mOffset(0u)
{
    init();
}


LinearAllocator::~LinearAllocator()
{
    if (isInitialized())
    {
        free(mBuffer);
        mBuffer = nullptr;
    }
}


void LinearAllocator::init()
{
    if (isInitialized())
    {
        PDG_ASSERT(false, "Attempt to init LinearAllocator wich is initialized already!");
        // TODO: log error
        return;
    }

    if (mBufferSize == 0u)
    {
        PDG_ASSERT(false, "Attempt to init LinearAllocator with 0 buffer size!");
        // TODO: log error
        return;
    }

    mBuffer = malloc(mBufferSize);
    PDG_ASSERT(mBuffer != nullptr, "Failed to init LinearAllocator buffer");
    reset();
}


void LinearAllocator::reset()
{
    if (!isInitialized())
    {
        PDG_ASSERT(false, "Attempt to reset LinearAllocator wich isn't initialized!"); // TODO: ??
        // TODO: log error
        return;
    }

    mOffset = 0u;
}


void * LinearAllocator::allocate(std::size_t const size, std::size_t const alignment)
{
    PDG_ASSERT(isInitialized(),
                "Attempt to allocate with LinearAllocator wich isn't initialized!");
    if (!isInitialized())
    {
        // TODO: log error
        return nullptr;
    }

    std::uintptr_t newBlockAddr = (std::uintptr_t)mBuffer + mOffset;

    std::size_t adjustment = 0u;
    if (alignment != 0u && (mOffset % alignment) != 0)
    {
        adjustment = calcAdjustment(newBlockAddr, alignment);
        PDG_ASSERT(adjustment != 0u, "Memory adjustment must not be 0!");
    }

    if (mOffset + adjustment + size > mBufferSize)
    {
        PDG_ASSERT(false, "Not enough memory!");
        // TODO: log error
        return nullptr;
    }

    newBlockAddr += adjustment;
    mOffset += (adjustment + size);

    std::cout << "LinearAllocator allocated " << size << " bytes at " << (void *)newBlockAddr << ";"
              << std::endl
              << "\talignment: " << alignment << "; adjustment: " << adjustment << ";" << std::endl
              << "\toffset: " << mOffset << ";" << std::endl;
    return (void *)(newBlockAddr);
}


void LinearAllocator::deallocate(void * ptr)
{
    PDG_ASSERT(false, "LinearAllocator doesn't free memory object by object; instead, the reset() method should be used, which marks all memory owned by the allocator as free.");
}


void LinearAllocator::setBufferSize(std::size_t const bufferSize)
{
    PDG_ASSERT(mBufferSize == 0u, "Attempt to set LinearAllocator buffer size repeatedly");
    if (mBufferSize != 0u)
    {
        // TODO: log error
        return;
    }
    PDG_ASSERT(bufferSize != 0u, "Attempt to set LinearAllocator buffer size to 0");
    if (bufferSize == 0u)
    {
        // TODO: log error
        return;
    }
    mBufferSize = bufferSize;
}


} // namespace pdg::core
