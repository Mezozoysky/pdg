#include <pdg/log/log.hpp>
#include <pdg/core/assert.hpp>

#include <fmt/format.h>


namespace pdg::log
{


Log::Log()
: Logger(this, LOGGER_TAG_DELIM)
, mEnabledLevels{MAX}
, mEnabledCats{DEFAULT}
, mLevel{MAX}
, mSinks{}
, mLoggers{}
{
    mSinks.emplace_back(new MemorySink());
    setupLevels();
}


Log::~Log()
{
    mLoggers.clear();
    mSinks.clear();
    mEnabledCats.clear();
    mEnabledLevels.clear();
}


void Log::setLevel(Level const & level)
{
    PDG_ASSERT(isLevelEnabled(level), "Can't set log level: level is disabled");
    if (!isLevelEnabled(level))
    {
        return;
    }
    mLevel = level;
}


void Log::setLevel(std::string const & levelName)
{
    auto const it = std::find_if(mEnabledLevels.begin(),
                           mEnabledLevels.end(),
                           [&levelName](Level const & enabledLevel)
                           { return enabledLevel.getName() == levelName; });
    PDG_ASSERT(it != mEnabledLevels.end(),
                fmt::format("Log level isn't found within enabled levels by name '{}'", levelName)
                        .c_str());
    if (it == mEnabledLevels.end())
    {
        return;
    }
    setLevel(*it);
}


void Log::enableLevel(Level const & level)
{
    for (auto const & l : mEnabledLevels)
    {
        if (level.getName() == l.getName())
        {
            auto errmsg = fmt::format("Log level with same name ('{}', {}) is already enabled",
                                      l.getName(),
                                      l.getPriority());
            PDG_ASSERT(false, errmsg.c_str());
            return;
        }

        if (level.getPriority() == l.getPriority())
        {
            auto errmsg = fmt::format("Log level with same priority ('{}', {}) is already enabled",
                                      l.getName(),
                                      l.getPriority());
            PDG_ASSERT(false, errmsg.c_str());
            return;
        }
    }
    mEnabledLevels.insert(level);
}


void Log::disableLevel(Level const & level)
{
    PDG_ASSERT(mEnabledLevels.contains(level),
                "Trying to disable log level which is not enabled");
    if (!mEnabledLevels.contains(level))
    {
        return;
    }

    PDG_ASSERT(level != MAX, "Disablig MAX level is forbidden");
    if (level == MAX)
    {
        return;
    }

    if (level == mLevel)
    {
        setLevel(MAX);
    }

    mEnabledLevels.erase(level);
}


void Log::enableCategory(Category const & cat)
{
    for (auto const & c : mEnabledCats)
    {
        PDG_ASSERT(cat.getName() != c.getName(), "Log category with same name is already enabled");
        if (cat.getName() == c.getName())
        {
            return;
        }
    }
    mEnabledCats.insert(cat);
}


void Log::disableCategory(Category const & cat)
{
    PDG_ASSERT(mEnabledCats.contains(cat),
                "Trying to disable log category which is not enabled");
    if (!mEnabledCats.contains(cat))
    {
        return;
    }

    PDG_ASSERT(cat != DEFAULT, "Disablig DEFAULT category is forbidden");
    if (cat == DEFAULT)
    {
        return;
    }

    mEnabledCats.erase(cat);
}


bool Log::addLogger(Logger const & logger)
{
    if (hasLogger(logger.getTag()))
    {
        PDG_ASSERT(false, fmt::format("Logger with the same tag '{}' already exists", logger.getTag()).c_str());
        return false;
    }
    auto const p = mLoggers.emplace(logger.getTag(), logger);
    return p.second;
}


Logger Log::findLogger(std::string const & tag) const
{
    auto it = mLoggers.find(tag);
    return (it == mLoggers.end() ? Logger{} : it->second);
}

bool Log::removeLogger(std::string const & tag)
{
    if (!hasLogger(tag))
    {
        PDG_ASSERT(hasLogger(tag),
                    fmt::format("Attempt to remove logger '{}' which is not added", tag).c_str());
        return false;
    }
    mLoggers.erase(tag);
    return true;
}


void Log::setupLevels() noexcept
{
    enableLevel(TRACE);
    enableLevel(DEBUG);
    enableLevel(INFO);
    enableLevel(WARNING);
    enableLevel(ERROR);
    enableLevel(FATAL);

    setLevel(INFO);
}


void Log::setupSinks(std::vector<Sink> const & sinks)
{
    PDG_ASSERT(mSinks.size() == 1u, "Sinks are already set");
    if (mSinks.size() != 1u)
    {
        return;
    }

    PDG_ASSERT(!sinks.empty(), "Attempt to set empty vector as sink");
    if (sinks.empty())
    {
        return;
    }

    Sink sink = mSinks[0];
    auto * memorySink = dynamic_cast<MemorySink *>(mSinks[0].getImpl());
    PDG_ASSERT(memorySink != nullptr, "MemorySink ptr must not be null");

    mSinks.clear();

    for (auto const & sink : sinks)
    {
        PDG_ASSERT(!sink.isNull(), "Attempt to add null sink");
        if (sink.isNull())
        {
            continue;
        }
        mSinks.push_back(sink);
    }

    if (memorySink != nullptr)
    {
        for (auto const & msg : memorySink->getMessages())
        {
            for (auto & sink : mSinks)
            {
                sink.write(msg);
            }
        }
    }

    memorySink->clearMessages();
}


} // pdg::log

