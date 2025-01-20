#include <pdg/core/dumb_allocator.hpp>
#include <pdg/core/assert.hpp>

#include <iostream>


namespace pdg::core
{


void DumbAllocator::init()
{
    PDG_ASSERT(false, "Attempt to init DumbAllocator!");
}


void * DumbAllocator::allocate(std::size_t const size, std::size_t const alignment)
{
    void * ptr = malloc(size);
    std::cout << "DumbAllocator allocated " << size << " bytes at " << ptr << std::endl;
    return ptr;
}


void DumbAllocator::deallocate(void * ptr)
{
    std::cout << "DumbAllocator deallocating at " << ptr << std::endl;
    PDG_ASSERT(ptr != nullptr, "Attempt to deallocate null pointer!");
    free(ptr);
}


} // namespace pdg::core
