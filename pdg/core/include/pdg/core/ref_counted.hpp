#pragma once

#include "assert.hpp"
#include <cstddef>

namespace pdg::core
{


class RefCounted
{
public:
    RefCounted() = default;
    RefCounted(RefCounted const & other) = default;
    RefCounted(RefCounted && other) noexcept = default;
    virtual ~RefCounted() noexcept = default;

    RefCounted & operator=(RefCounted const & other) = default;
    RefCounted & operator=(RefCounted && other) = default;

    inline void incRefCount();
    inline void decRefCount();
    inline std::size_t getRefCount() const noexcept;

private:
    mutable std::size_t mRefCount{0u};
};


// inline/template members



inline void RefCounted::incRefCount()
{
    ++mRefCount;
}


inline void RefCounted::decRefCount()
{
    PDG_ASSERT(mRefCount > 0u, "Ref count must be greater than 0 then decrementing");
    if (mRefCount > 0u)
    {
        --mRefCount;
    }
    if (mRefCount == 0u)
    {
        delete this;
    }
}

inline std::size_t RefCounted::getRefCount() const noexcept
{
    return mRefCount;
}


} // namespace pdg::core

