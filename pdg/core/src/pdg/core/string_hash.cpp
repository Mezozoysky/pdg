#include <pdg/core/string_hash.hpp>
#include <pdg/core/assert.hpp>

#include <xxhash.h>

#include <cstring>


namespace pdg::core
{


#if defined(PDG_SYSTEM_64BIT)
    using HashValueType = XXH64_hash_t;
#elif defined(PDG_SYSTEM_32BIT)
    using HashValueType = XXH32_hash_t;
#else
#error "Unknown system bitness"
#endif


std::size_t hashRawString(char const * string, std::size_t length)
{
	if (string == nullptr)
	{
        PDG_ASSERT(length == 0u, "Null pointers are only allowed with 0 length");
        length = 0u;
	}
    else
	{
        if (length == 0u)
        {
            length = std::strlen(string);
        }
	}

    //HashValueType value{0u};
#if defined(PDG_SYSTEM_64BIT)
    auto value = XXH3_64bits(static_cast<void const *>(string), length);
#elif defined(PDG_SYSTEM_32BIT)
    auto value = XXH32(string, length, 22u);
#else
#error "Unknown system bitness"
#endif
    PDG_ASSERT(value != 0u, "Invalid hash!");
    return value;
}


StringHash::StringHash()
: mValue{0u}
{
}


StringHash::StringHash(std::string const & string)
: mValue{hashRawString(string.c_str(), string.length())}
#if defined(PDG_DEBUG) && defined(PDG_DEBUG_STRING_HASH)
, mDbgStr{string};
#endif
{
}


StringHash::StringHash(std::string_view stringView)
: mValue{hashRawString(stringView.data(), stringView.length())}
#if defined(PDG_DEBUG) && defined(PDG_DEBUG_STRING_HASH)
, mDbgStr{stringView};
#endif
{
}


StringHash::StringHash(char const * const stringRaw, std::size_t length)
: mValue{hashRawString(stringRaw, length)}
#if defined(PDG_DEBUG) && defined(PDG_DEBUG_STRING_HASH)
, mDbgStr{string};
#endif
{
}


} // pdg::core

