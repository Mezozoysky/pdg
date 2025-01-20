#pragma once


namespace pdg::core
{


template<bool initialValue>
class FragileBool
{
public:
    inline FragileBool() noexcept;
    ~FragileBool() noexcept = default;

    FragileBool & operator=(FragileBool const & other) noexcept;
    FragileBool & operator=(bool value) noexcept;
    inline operator bool() const noexcept;

    void setValue(bool newValue) noexcept;
    inline bool getValue() const noexcept;

private:
    bool mValue;
};


// template/inline members


template<bool initialValue>
inline FragileBool<initialValue>::FragileBool() noexcept
: mValue{initialValue}
{
}


template<bool initialValue>
FragileBool<initialValue> & FragileBool<initialValue>::operator =(FragileBool const & other) noexcept
{
setValue(other.getValue());
return *this;
}


template<bool initialValue>
FragileBool<initialValue> & FragileBool<initialValue>::operator =(bool value) noexcept
{
setValue(value);
return *this;
}


template<bool initialValue>
inline FragileBool<initialValue>::operator bool() const noexcept
{
    return mValue;
}


template<bool initialValue>
void FragileBool<initialValue>::setValue(bool newValue) noexcept
{
    if (newValue == initialValue || newValue == mValue)
    {
        return;
    }
    mValue = newValue;
}


template<bool initialValue>
inline bool FragileBool<initialValue>::getValue() const noexcept
{
    return mValue;
}


} // namespace pdg::core

