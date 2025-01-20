#pragma once

#include <string>


namespace pdg::cnfg::impl
{


template<typename T>
bool parseFromString(std::string const & str, T & value)
{
//     static_assert(false, "parseFromString isn't overriden for given type");
    return false;
}

template<>
bool parseFromString<bool>(std::string const & str, bool & value);

template<>
bool parseFromString<std::string>(std::string const & str, std::string & value);

template<>
bool parseFromString<std::uint32_t>(std::string const & str, std::uint32_t & value);


} // namespace pdg::cnfg::impl

