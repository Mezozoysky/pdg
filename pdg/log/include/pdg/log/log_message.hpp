#pragma once

#include "category.hpp"
#include "level.hpp"


namespace pdg::log
{


struct LogMessage
{
    Category category;
    Level level;
    std::string tag;
    std::string message;

    LogMessage()
    : category{DEFAULT}
    , level{MAX}
    , tag{}
    , message{}
    {
    }

    LogMessage(Category cat, Level lvl, std::string_view loggerTag, std::string_view msg)
    : category{cat}
    , level{lvl}
    , tag{loggerTag}
    , message{msg}
    {
    }

    inline bool isNull() const noexcept
    {
        return message.empty();
    }
};


} // namespace pdg::log

