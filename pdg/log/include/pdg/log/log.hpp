#pragma once

#include "logger.hpp"
#include "level.hpp"
#include "category.hpp"
#include "sink.hpp"
#include <pdg/core/assert.hpp>

#include <string_view>
#include <vector>
#include <limits>
#include <memory>
#include <unordered_map>


namespace pdg::log
{


class Log
: public Logger
{
public:
    Log();
    Log(Log const & other) = delete;
    Log(Log && other) = default;
    virtual ~Log();

    Log & operator=(Log const & other) = delete;
    Log & operator=(Log && other) = default;

    using Logger::getLogger;
    inline Logger getLogger() const noexcept;

    inline Level const & getLevel() const noexcept;
    void setLevel(Level const & level);
    void setLevel(std::string const & levelName);

    inline bool isLevelEnabled(Level const &) const noexcept;
    void enableLevel(Level const &);
    void disableLevel(Level const &);

    inline bool isCategoryEnabled(Category const &) const noexcept;
    void enableCategory(Category const &);
    void disableCategory(Category const &);

    void setupSinks(std::vector<Sink> const & sinks);
    inline std::vector<Sink> const & getSinks() const noexcept;

    bool addLogger(Logger const & logger);
    inline bool hasLogger(std::string const & tag) const noexcept;
    Logger findLogger(std::string const & tag) const;
    bool removeLogger(std::string const & tag);

private:
    void setupLevels() noexcept;

private:
    std::set<Level> mEnabledLevels;
    std::set<Category> mEnabledCats;
    Level mLevel;

    std::vector<Sink> mSinks;
    std::unordered_map<std::string, Logger> mLoggers;
};


// inline members

inline Logger Log::getLogger() const noexcept
{
    return Logger{*this};
}


inline Level const & Log::getLevel() const noexcept
{
    return mLevel;
}


inline bool Log::isLevelEnabled(Level const & level) const noexcept
{
    return mEnabledLevels.contains(level);
}


inline bool Log::isCategoryEnabled(Category const & cat) const noexcept
{
    return mEnabledCats.contains(cat);
}


inline std::vector<Sink> const & Log::getSinks() const noexcept
{
    return mSinks;
}


inline bool Log::hasLogger(std::string const & tag) const noexcept
{
    return mLoggers.contains(tag);
}


} // namespace pdg::log

