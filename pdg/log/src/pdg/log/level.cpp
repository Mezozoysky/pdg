#include <pdg/log/level.hpp>
#include <pdg/log/log.hpp>
#include <pdg/core/assert.hpp>


namespace pdg::log
{


Level::Level(std::string_view name, int priority)
: mName{name}
, mPriority{priority}
{
}


} // namespace pdg::log

