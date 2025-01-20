#pragma once

#include "ref_counted.hpp"
#include "assert.hpp"
#include <type_traits>


namespace pdg::core
{


template<typename T>
class Ptr
{
public:
    Ptr();
    Ptr(Ptr const & other);
    Ptr(Ptr && other) noexcept;
    Ptr(T * rawPtr = nullptr);
    template<typename U>
    Ptr(Ptr<U> const & other);
    template<typename U>
    Ptr(Ptr<U> && other);

    ~Ptr();

    Ptr & operator=(Ptr const & other);
    Ptr & operator=(Ptr && other) noexcept;
    Ptr & operator=(T * rawPtr);
    template<typename U>
    Ptr & operator=(Ptr<U> const & other);
    template<typename U>
    Ptr & operator=(Ptr<U> && other);

    template<typename U>
    static Ptr<T> static_pointer_cast(Ptr<U> const & other);
    template<typename U>
    static Ptr<T> dynamic_pointer_cast(Ptr<U> const & other);

    inline T & operator*();
    inline T * operator->();

    void reset();
    inline bool isNull() const noexcept;

    T * get() const noexcept;

private:
    void acquire(T * rawPtr);
    void release();

private:
    T * mPtr;
};


template<typename T>
Ptr<T>::Ptr()
: mPtr{nullptr}
{
    static_assert(std::is_base_of_v<RefCounted, T>, "T must be RefCounted!");
}


template<typename T>
Ptr<T>::Ptr(Ptr const & other)
: mPtr{nullptr}
{
    static_assert(std::is_base_of_v<RefCounted, T>, "T must be RefCounted!");

    if (other.isNull())
    {
        return;
    }

    acquire(other.mPtr);
}

template<typename T>
Ptr<T>::Ptr(Ptr && other) noexcept
: mPtr{nullptr}
{
    static_assert(std::is_base_of_v<RefCounted, T>, "T must be RefCounted!");

    if (other.isNull())
    {
        return;
    }

    mPtr = other.mPtr;
    other.mPtr = nullptr;
}

template<typename T>
Ptr<T>::Ptr(T * rawPtr)
: mPtr{nullptr}
{
    static_assert(std::is_base_of_v<RefCounted, T>, "T must be RefCounted!");

    if (!rawPtr)
    {
        return;
    }

    acquire(rawPtr);
}


template<typename T>
template<typename U>
Ptr<T>::Ptr(Ptr<U> const & other)
: mPtr{nullptr}
{
    static_assert(std::is_base_of_v<RefCounted, T>, "T must be RefCounted!");
    static_assert(std::is_base_of_v<T, U>, "U must be derived from T");

    if (other.isNull())
    {
        return;
    }

    acquire(static_cast<T *>(other.get()));
}


template<typename T>
template<typename U>
Ptr<T>::Ptr(Ptr<U> && other)
: mPtr{nullptr}
{
    static_assert(std::is_base_of_v<RefCounted, T>, "T must be RefCounted!");
    static_assert(std::is_base_of_v<T, U>, "U must be derived from T");

    if (other.isNull())
    {
        return;
    }

    mPtr = static_cast<T *>(other.mPtr);
    other.mPtr = nullptr;
}


template<typename T>
Ptr<T>::~Ptr()
{
    release();
}


template<typename T>
Ptr<T> & Ptr<T>::operator=(Ptr const & other)
{
    if (this == &other)
    {
        return *this;
    }

    if (mPtr == other.mPtr)
    {
        return *this;
    }

    if (other.isNull())
    {
        release();
    }
    else
    {
        acquire(other.mPtr);
    }

    return *this;
}


template<typename T>
Ptr<T> & Ptr<T>::operator=(Ptr && other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    if (mPtr == other.mPtr)
    {
        return *this;
    }

    release();

    if (!other.isNull())
    {
        mPtr = other.mPtr;
        other.mPtr = nullptr;
    }

    return *this;
}


template<typename T>
Ptr<T> & Ptr<T>::operator=(T * rawPtr)
{
    if (mPtr == rawPtr)
    {
        return;
    }

    release();

    if (rawPtr)
    {
        acquire(rawPtr);
    }
}


template<typename T>
template<typename U>
Ptr<T> & Ptr<T>::operator=(Ptr<U> const & other)
{
    if (mPtr == static_cast<T *>(other.mPtr))
    {
        return *this;
    }

    if (other.isNull())
    {
        release();
    }
    else
    {
        acquire(static_cast<T *>(other.mPtr));
    }

    return *this;
}


template<typename T>
template<typename U>
Ptr<T> & Ptr<T>::operator=(Ptr<U> && other)
{
    if (mPtr == static_cast<T *>(other.mPtr))
    {
        return *this;
    }

    release();

    if (!other.isNull())
    {
        mPtr = static_cast<T *>(other.mPtr);
        other.mPtr = nullptr;
    }

    return *this;
}


template <typename T>
template <typename U>
Ptr<T> Ptr<T>::static_pointer_cast(const Ptr<U>& other)
{
    static_assert(std::is_base_of_v<T, U>, "U must be derived from T!");
    T * ptr = static_cast<T *>(other.mPtr);
    return Ptr<T>(ptr);
}


template <typename T>
template <typename U>
Ptr<T> Ptr<T>::dynamic_pointer_cast(const Ptr<U> & other)
{
    static_assert(std::is_base_of_v<U, T>, "T must be derived from U!");
    T * ptr = dynamic_cast<T *>(other.mPtr);
    return Ptr<T>(ptr);
}


template<typename T>
inline T & Ptr<T>::operator*()
{
    return *mPtr;
}


template<typename T>
inline T * Ptr<T>::operator->()
{
    return mPtr;
}


template<typename T>
void Ptr<T>::reset()
{
    release();
}


template<typename T>
inline bool Ptr<T>::isNull() const noexcept
{
    return mPtr == nullptr;
}


template<typename T>
inline T * Ptr<T>::get() const noexcept
{
    return mPtr;
}


template<typename T>
void Ptr<T>::acquire(T * rawPtr)
{
    release();

    if (!rawPtr)
    {
        return;
    }

    mPtr = rawPtr;
    mPtr->incRefCount();
}


template<typename T>
void Ptr<T>::release()
{
    if (isNull())
    {
        return;
    }

    mPtr->decRefCount();
    mPtr = nullptr;
}



} // namespace pdg::core

