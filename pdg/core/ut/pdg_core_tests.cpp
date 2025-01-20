#include <catch2/catch_test_macros.hpp>

#include <pdg/core/dumb_allocator.hpp>
#include <pdg/core/linear_allocator.hpp>
#include <pdg/core/stack_allocator.hpp>

#include <iostream>
#include <cstdint>
#include <memory>


using namespace pdg;


class DumbAllocObject : public core::CustomAllocatible<DumbAllocObject, core::DumbAllocator>
{
public:
    std::uint64_t data[2];
};


TEST_CASE("Dumb allocator tests", "[allocator,dumb_allocator]")
{
    std::cout << "=== DumbAllocator ===" << std::endl;

    auto * dumbObj = new DumbAllocObject();
    REQUIRE(dumbObj != nullptr);

    delete dumbObj;
    dumbObj = nullptr;

    auto dumbObjUPtr = std::make_unique<DumbAllocObject>();
    REQUIRE(dumbObjUPtr);
}


TEST_CASE("Linear allocator tests", "[allocator,linear_allocator]")
{
    std::cout << std::endl << "=== LinearAllocator ===" << std::endl;

    core::LinearAllocator la{128u};

    std::uint8_t * bytePtr = (std::uint8_t *)(la.allocate(sizeof(std::uint8_t),  alignof(std::max_align_t)));
    REQUIRE(bytePtr != nullptr);
    *bytePtr = 8u;

    std::uint64_t * qwordPtr = (std::uint64_t *)(la.allocate(sizeof(std::uint64_t),  alignof(std::max_align_t)));
    REQUIRE(qwordPtr != nullptr);
    *qwordPtr = 0xf0f0f0f0f0f0f0f0;

    std::uint32_t * dwordPtr = (std::uint32_t *)(la.allocate(sizeof(std::uint32_t),  alignof(std::max_align_t)));
    REQUIRE(dwordPtr != nullptr);
    *dwordPtr = 0xf0f0f0f0;

    bytePtr = (std::uint8_t *)(la.allocate(sizeof(std::uint8_t),  alignof(std::max_align_t)));
    REQUIRE(bytePtr != nullptr);
    *bytePtr = 22u;

    dwordPtr = nullptr;
    qwordPtr = nullptr;
    bytePtr = nullptr;
    la.reset();
    //REQUIRE(la.getFreeSize() == 128u - sizeof(std::uint8_t));
}


struct TheStruct
{
    std::uint8_t byte;
    std::uint64_t qwords[4];
};


TEST_CASE("Stack allocator tests", "[allocator,stack_allocator]")
{
    std::cout << std::endl << "=== StackAllocator ===" << std::endl;

    core::StackAllocator sa{256u};
    REQUIRE(sa.getBufferSize() == 256u);
    REQUIRE(sa.getUsedSize() == 0u);
    REQUIRE(sa.getFreeSize() == 256u);

    TheStruct * ptr = (TheStruct *)(sa.allocate(sizeof(TheStruct), alignof(TheStruct)));
    REQUIRE(ptr != nullptr);
    REQUIRE(sa.getUsedSize() == sizeof(TheStruct) + alignof(TheStruct));
    REQUIRE(sa.getFreeSize() == sa.getBufferSize() - sizeof(TheStruct) - alignof(TheStruct));
    ptr->byte = 8u;

    ptr = (TheStruct *)(sa.allocate(sizeof(TheStruct), alignof(TheStruct)));
    REQUIRE(ptr != nullptr);
    ptr->byte = 16u;

    ptr = (TheStruct *)(sa.allocate(sizeof(TheStruct), alignof(TheStruct)));
    REQUIRE(ptr != nullptr);
    ptr->byte = 32u;

    ptr = (TheStruct *)(sa.allocate(sizeof(TheStruct), alignof(TheStruct)));
    REQUIRE(ptr != nullptr);
    ptr->byte = 64u;

    sa.deallocate(ptr);
    ptr = nullptr;

    sa.reset();
}
