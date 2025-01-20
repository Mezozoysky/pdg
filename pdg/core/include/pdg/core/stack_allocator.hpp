#pragma once

#include <pdg/core/build_config.hpp>

#include "allocator.hpp"


namespace pdg::core
{


class StackAllocator final
: public Allocator
{
public:
    StackAllocator();
    explicit StackAllocator(std::size_t const bufferSize);
    virtual ~StackAllocator();

    virtual void init() override;
    void reset();

    [[nodiscard]] virtual void * allocate(std::size_t const size, std::size_t const alignment) override;
    virtual void deallocate(void * ptr = nullptr) override;

    inline bool isInitialized() const noexcept
    {
        return (mBuffer != nullptr);
    }

    void setBufferSize(std::size_t const bufferSize);

    inline std::size_t getBufferSize() const noexcept
    {
        return mBufferSize;
    }

    inline std::size_t getUsedSize() const noexcept
    {
        return mOffset;
    }

    inline std::size_t getFreeSize() const noexcept
    {
        return mBufferSize - mOffset;
    }

private:
    void * mBuffer;
    std::size_t mBufferSize;
    std::size_t mOffset;
};


} // namespace pdg::core
