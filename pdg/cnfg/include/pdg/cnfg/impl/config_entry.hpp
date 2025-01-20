#pragma once

#include <cstdint>
#include <string>

#include "parsing.hpp" // for ConfigEntryImpl only


namespace pdg::cnfg::impl
{


class ConfigEntry
{
public:
    inline ConfigEntry();
    virtual ~ConfigEntry() noexcept = default;

    inline bool hasValue() const noexcept;
    inline bool hasDefaultValue() const noexcept;
    inline bool hasObtainedValue() const noexcept;

    virtual bool setValueFromString(std::string const & str) = 0;

protected:
    enum Flags : std::uint8_t
    {
        FLAG_IS_OPTIONAL    = 1u,
        FLAG_IS_OBTAINED    = 2u
    };

    inline bool isOptional() const noexcept;
    inline void setOptional() noexcept;
    inline bool isObtained() const noexcept;
    inline void setObtained() noexcept;

private:
    std::uint8_t mFlags;
};


template<typename ValueT>
class ConfigEntryTyped : public ConfigEntry
{
public:
    ConfigEntryTyped()
    : mValue{}
    {
    }
    virtual ~ConfigEntryTyped() = default;

    bool setDefaultValue(ValueT && value);
    bool setValue(ValueT && value);
    virtual bool setValueFromString(std::string const & str) override final;
    bool getValue(ValueT & value) const;

private:
    ValueT mValue;
};


// === inline members ===

inline ConfigEntry::ConfigEntry()
: mFlags{0u}
{
}

inline bool ConfigEntry::hasValue() const noexcept
{
    return isOptional() || isObtained();
}

inline bool ConfigEntry::hasDefaultValue() const noexcept
{
    return isOptional() && !isObtained();
}

inline bool ConfigEntry::hasObtainedValue() const noexcept
{
    return isObtained();
}


inline bool ConfigEntry::isOptional() const noexcept
{
    return (mFlags & FLAG_IS_OPTIONAL);
}

inline bool ConfigEntry::isObtained() const noexcept
{
    return (mFlags & FLAG_IS_OBTAINED);
}

inline void ConfigEntry::setOptional() noexcept
{
    mFlags |= FLAG_IS_OPTIONAL;
}

inline void ConfigEntry::setObtained() noexcept
{
    mFlags |= FLAG_IS_OBTAINED;
}


// === template members ===

template<typename ValueT>
bool ConfigEntryTyped<ValueT>::setDefaultValue(ValueT && value)
{
    if (hasValue())
    {
        // TODO: log error
        return false;
    }

    mValue = std::move(value);
    setOptional();

    return true;
}


template<typename ValueT>
bool ConfigEntryTyped<ValueT>::setValue(ValueT && value)
{
    if (hasObtainedValue())
    {
        // TODO: log error
        return false;
    }

    mValue = std::move(value);
    setObtained();

    return true;
}


template<typename ValueT>
bool ConfigEntryTyped<ValueT>::setValueFromString(std::string const & str)
{
    ValueT value{};
    bool const success = parseFromString<ValueT>(str, value);
    if (success)
    {
        mValue = std::move(value);
        setObtained();
    }
    return success;
}


template<typename ValueT>
bool ConfigEntryTyped<ValueT>::getValue(ValueT & value) const
{
    if (hasValue())
    {
        value = mValue;
        return true;
    }
    return false;
}


} // namespace pdg::cnfg::impl

