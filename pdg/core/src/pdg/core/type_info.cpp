#include <pdg/core/type_info.hpp>

namespace pdg::core
{

TypeInfo::TypeInfo() noexcept
: mTypeName{nullptr}
, mBaseInfo{nullptr}
{}

TypeInfo::TypeInfo(char const * const typeName, TypeInfo const * const baseInfo) noexcept
: mTypeName{typeName}
, mBaseInfo{baseInfo}
{}


} // namespace pdg::core
