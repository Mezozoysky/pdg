#include <pdg/cnfg/impl/parsing.hpp>
#include <pdg/core/string_utils.hpp>


namespace pdg::cnfg::impl
{


template<>
bool parseFromString<bool>(std::string const & str, bool & value)
{
    return core::parseBool(str, value);
}


template<>
bool parseFromString<std::string>(std::string const & str, std::string & value)
{
    value = str;
    return true;
}


template<>
bool parseFromString<std::uint32_t>(std::string const & str, std::uint32_t & value)
{
    return core::parseNumber<std::uint32_t>(str, value);
}


} // namespace pdg::cnfg::impl

