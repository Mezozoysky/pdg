#include <pdg/log/logger.hpp>
#include <pdg/log/log.hpp>
#include <pdg/log/log_message.hpp>

#include <pdg/core/assert.hpp>

#include <fmt/format.h>

#include <sstream>


namespace pdg::log
{


Logger::Logger()
: mLog{nullptr}
, mTag{}
{
}

Logger::Logger(Log * const log, std::string_view tag)
: mLog{log}
, mTag{tag}
{
    PDG_ASSERT(log != nullptr,
                fmt::format("Attempt to create logger with null log (tag: '{}')", tag).c_str());
}


Logger::Logger(Logger const & other)
: mLog{other.mLog}
, mTag{other.mTag}
{
}


Logger::~Logger()
{
}


Logger & Logger::operator=(Logger const & other)
{
    mLog = other.mLog;
    mTag = other.mTag;

    return *this;
}


Log * const Logger::getLog() const noexcept
{
    return mLog;
}


std::string const & Logger::getTag() const noexcept
{
    return mTag;
}


void Logger::write(Category const & cat, Level const & level, std::string_view message) const
{
    PDG_ASSERT(!isNull(), "Must not be called on null logger");
    if (isNull())
    {
        return;
    }

    PDG_ASSERT(getLog()->isLevelEnabled(level),
                fmt::format("Log level '{}' is disabled", level.getName()).c_str());
    if (!getLog()->isLevelEnabled(level))
    {
        return;
    }

    if (!getLog()->isCategoryEnabled(cat))
    {
        return;
    }

    if (level < getLog()->getLevel())
    {
        return;
    }

    for (auto const & sink : getLog()->getSinks())
    {
        sink.write(LogMessage{cat, level, getTag(), message});
    }
}


Logger Logger::getLogger(std::string_view tag) const
{
    PDG_ASSERT(!isNull(), "Attempt to get logger from null logger");
    if (isNull())
    {
        return Logger{};
    }

    PDG_ASSERT(!tag.empty(), "Logger tag must not be empty");
    if (tag.empty())
    {
        //return Logger{};
        return getLog()->getLogger();
    }

    if (tag == LOGGER_TAG_DELIM)
    {
        return getLog()->getLogger();
    }

    std::string newTag;
    {
        std::ostringstream tagStream{};

        if (tag.starts_with(LOGGER_TAG_DELIM))
        {
            tagStream << tag;
        }
        else
        {
            tagStream << getTag();
            if (getTag() != LOGGER_TAG_DELIM)
            {
                tagStream << LOGGER_TAG_DELIM;
            }
            tagStream << tag;
        }

        newTag = tagStream.str();
    }

    Logger logger = getLog()->findLogger(newTag);
    if (logger.isNull()) // not found
    {
        logger = Logger{getLog(), newTag};
        PDG_ASSERT(!logger.isNull(), fmt::format("Failed to create logger (tag: '{}')", newTag).c_str());
        if (logger.isNull())
        {
            return logger;
        }

        if (!getLog()->addLogger(logger))
        {
            PDG_ASSERT(false, fmt::format("Failed to add logger into log (tag: '{}')", newTag).c_str());
        }
    }
    return logger;
}


} // namespace pdg::log

