#pragma once

#include <pdg/core/build_config.hpp>

#include "allocator.hpp"


namespace pdg::core
{


class LinearAllocator final
:public Allocator
{
public:
    LinearAllocator();
    explicit LinearAllocator(std::size_t const bufferSize);
    virtual ~LinearAllocator();

    virtual void init() override;
    void reset();

    [[nodiscard]] virtual void * allocate(std::size_t const size, std::size_t const alignment) override;
    virtual void deallocate(void * ptr = nullptr) override;

    inline bool isInitialized() const noexcept
    {
        return (mBuffer != nullptr);
    }

    void setBufferSize(std::size_t const bufferSize);

private:
    void * mBuffer;
    std::size_t mBufferSize;
    std::size_t mOffset;
};


} // namespace pdg::core
