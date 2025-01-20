#pragma once

#include <set>
#include <string_view>
#include <string>
#include <limits>

namespace pdg::log
{


class Level
{
public:
    explicit Level(std::string_view name, int priority);
    ~Level() noexcept = default;

    inline std::string const & getName() const noexcept;
    inline int getPriority() const noexcept;

    friend bool operator<(Level const & a, Level const & b);
    friend bool operator>(Level const & a, Level const & b);
    friend bool operator==(Level const & a, Level const & b);
    friend bool operator!=(Level const & a, Level const & b);

private:
    std::string mName;
    int mPriority;
};


static Level const MAX{"", std::numeric_limits<int>::max()};

static Level const TRACE{"TRACE", -2000};
static Level const DEBUG{"DEBUG", -1000};
static Level const INFO{"INFO", 0};
static Level const WARNING{"WARN", 1000};
static Level const ERROR{"ERROR", 2000};
static Level const FATAL{"FATAL", 3000};


// inline members

inline std::string const & Level::getName() const noexcept
{
    return mName;
}

inline int Level::getPriority() const noexcept
{
    return mPriority;
}


inline bool operator<(Level const & a, Level const & b)
{
    return (a.mPriority < b.mPriority);
}

inline bool operator>(Level const & a, Level const & b)
{
    return (a.mPriority > b.mPriority);
}

inline bool operator==(Level const & a, Level const & b)
{
    return (a.mPriority == b.mPriority);
}

inline bool operator!=(Level const & a, Level const & b)
{
    return !(a == b);
}



} // namespace pdg::log

