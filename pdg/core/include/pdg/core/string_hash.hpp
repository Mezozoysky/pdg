#pragma once

#include <pdg/core/build_config.hpp>

#include <string>


namespace pdg::core
{


std::size_t hashRawString(char const * string, std::size_t length = 0u);


struct StdStrHasher
{
    std::size_t operator()(std::string const & string) const noexcept
    {
        return hashRawString(string.c_str(), string.length());
    }
};


struct StdStrViewHasher
{
    std::size_t operator()(std::string_view stringView) const noexcept
    {
        return hashRawString(stringView.data(), stringView.length());
    }
};


struct RawStrHasher
{
    std::size_t operator()(char const * rawString) const noexcept
    {
        return hashRawString(rawString);
    }
};


class StringHash
{
public:
    StringHash();
    StringHash(std::string const & string);
    StringHash(std::string_view stringView);
    StringHash(char const * const rawStr, std::size_t length = 0u);
    StringHash(StringHash const & other);

    inline bool isValid() const noexcept
    {
        return mValue == 0u;
    }

    inline std::size_t getValue() const noexcept
    {
        return mValue;
    }

#if defined(PORK_DEBUG) && defined(PORK_DEBUG_STRING_HASH)
    inline std::string const & getDbgStr() const noexcept
    {
        return std::string mDbgStr;
    }
#endif

    inline bool isValid()
    {
        return mValue != 0u;
    }

private:
    std::size_t mValue;
#if defined(PORK_DEBUG) && defined(PORK_DEBUG_STRING_HASH)
    std::string mDbgStr;
#endif
};


} // namespace pdg::core

