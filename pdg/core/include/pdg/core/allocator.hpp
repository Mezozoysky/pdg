#pragma once

#include <pdg/core/build_config.hpp>

#include <cstddef>
#include <utility>


namespace pdg::core
{


class Allocator
{
public:
    Allocator() noexcept = default;
    virtual ~Allocator() noexcept = default;
    Allocator(Allocator const & other) = delete;
    Allocator & operator=(Allocator const & other) = delete;

    virtual void init() = 0;

    [[nodiscard]] virtual void * allocate(std::size_t const size, std::size_t const alignment = 0u) = 0;
    virtual void deallocate(void * ptr = nullptr) = 0;

    // TODO: is it usable?
    template<typename T>
    [[nodiscard]] void * allocate();

    // TODO: is it usable?
    template<typename T, typename... Args>
    [[nodiscard]] T * createObj(Args &&... args);
    // TODO: is it usable?
    template<typename T>
    void destroyObj(T *& ptr);
};


template<typename T>
void * Allocator::allocate()
{
    return allocate(sizeof(T), alignof(T));
}

template<typename T, typename... Args>
inline T * Allocator::createObj(Args &&... args)
{
    return new (allocate<T>()) T(std::forward<args>(args)...);
}

template<typename T>
inline void Allocator::destroyObj(T *& ptr)
{
    ptr->~T();
    deallocate(ptr);
    ptr = nullptr; // TODO: is it really needed?
}


template<typename DerivedT, typename AllocatorT>
class CustomAllocatible
{
public:
    CustomAllocatible() = default;
    virtual ~CustomAllocatible() noexcept = default;
    CustomAllocatible(CustomAllocatible const & other) = delete;
    CustomAllocatible & operator=(CustomAllocatible const & other) = delete;

    static AllocatorT allocator;

    static void * operator new(std::size_t size) noexcept(false)
    {
        return allocator.allocate(size, alignof(DerivedT));
    }

    static void operator delete(void * ptr) noexcept
    {
        allocator.deallocate(ptr);
    }
};

template<typename DerivedT, typename AllocatorT>
AllocatorT CustomAllocatible<DerivedT, AllocatorT>::allocator{};


} // namespace pdg::core
