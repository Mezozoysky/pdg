#include <pdg/core/stack_allocator.hpp>
#include <pdg/core/allocator_utils.hpp>
#include <pdg/core/assert.hpp>

#include <cstdlib>

#include <iostream>


namespace pdg::core
{


struct Header
{
    std::uint8_t adjustment;
};


StackAllocator::StackAllocator()
: mBuffer(nullptr)
, mBufferSize(0u)
, mOffset(0u)
{
}


StackAllocator::StackAllocator(std::size_t const bufferSize)
: mBuffer(nullptr)
, mBufferSize(bufferSize)
, mOffset(0u)
{
    init();
}


StackAllocator::~StackAllocator()
{
    if (isInitialized())
    {
        free(mBuffer);
        mBuffer = nullptr;
    }
}


void StackAllocator::init()
{
    if (isInitialized())
    {
        PDG_ASSERT(false, "Attempt to init StackAllocator wich is initialized already!");
        // TODO: log error
        return;
    }

    if (mBufferSize == 0u)
    {
        PDG_ASSERT(false, "Attempt to init StackAllocator with 0 buffer size!");
        // TODO: log error
        return;
    }

    mBuffer = malloc(mBufferSize);
    PDG_ASSERT(mBuffer != nullptr, "Failed to init StackAllocator buffer!");
    reset();
}


void StackAllocator::reset()
{
    if (!isInitialized())
    {
        PDG_ASSERT(false, "Attempt to reset StackAllocator which isn't initialized!"); // TODO: ??
        // TODO: log error
        return;
    }

    mOffset = 0u;
}


void * StackAllocator::allocate(std::size_t const size, std::size_t const alignment)
{
    PDG_ASSERT(isInitialized(), "Attempt to allocate with StackAllocator which isn't initialized!");
    if (!isInitialized())
    {
        // TODO: log error
        return nullptr;
    }

    std::uintptr_t addr = (std::uintptr_t)mBuffer + mOffset;

    std::size_t adjustment = calcAdjustment(addr, alignment, sizeof(Header));

    if (mOffset + size + adjustment > mBufferSize)
    {
        PDG_ASSERT(false, "Not enough memory!");
        // TODO: log error
        return nullptr;
    }

    addr += adjustment;
    mOffset += (adjustment + size);

    Header * headerPtr = (Header *)(addr - sizeof(Header));
    Header header{(std::uint8_t)adjustment};
    *headerPtr = std::move(header);

    std::cout << "StackAllocator allocated " << size << " bytes at " << (void *)addr << ";"
              << std::endl
              << "\talignment: " << alignment << ";" << std::endl
              << "\tadjustment: " << adjustment << ";" << std::endl
              << "\toffset: " << mOffset << ";" << std::endl;
    return (void *)addr;
}


void StackAllocator::deallocate(void * ptr)
{
    std::uintptr_t const addr = (std::uintptr_t)ptr;
    Header const * header = (Header *)(addr - sizeof(Header));

    //std::size_t const adjustment = header->adjustment;
    mOffset = addr - (std::uintptr_t)mBuffer - header->adjustment;

    std::cout << "StackAllocator deallocated at " << ptr << ";" << std::endl
              << "\tadjustment: " << (unsigned)(header->adjustment) << ";" << std::endl
              << "\toffset: " << mOffset << ";" << std::endl;
}


void StackAllocator::setBufferSize(std::size_t const bufferSize)
{
    PDG_ASSERT(mBufferSize == 0u, "Attempt to set StackAllocator buffer size repeatedly!");
    if (mBufferSize != 0u)
    {
        // TODO: log error
        return;
    }
    PDG_ASSERT(bufferSize != 0u, "Attempt to set StackAllocator buffer size to 0!");
    if (bufferSize == 0u)
    {
        // TODO: log error
        return;
    }
    mBufferSize = bufferSize;
}


} // namespace pdg::core
