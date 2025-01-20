#pragma once

#include <pdg/log/category.hpp>
#include <pdg/log/level.hpp>
#include <string>


namespace pdg::log
{


class Log;

static std::string const LOGGER_TAG_DELIM{"/"};


class Logger
{
public:
    Logger();
    Logger(Log * const log, std::string_view tag);
    Logger(Logger const & other);
    Logger(Logger && other) = default;
    virtual ~Logger();

    Logger & operator=(Logger const & other);
    Logger & operator=(Logger && other) = default;

    friend bool operator==(Logger const & a, Logger const & b);
    friend bool operator!=(Logger const & a, Logger const & b);
    friend bool operator==(Logger const & a, std::nullptr_t b);
    friend bool operator!=(Logger const & a, std::nullptr_t b);

    inline bool isNull() const noexcept;

    Log * const getLog() const noexcept;

    std::string const & getTag() const noexcept;

    Logger getLogger(std::string_view tag) const;

    void write(Category const & cat, Level const & level, std::string_view message) const;

    inline void write(Level const & level, std::string_view message) const;
    inline void write(std::string_view message) const;
    inline void trace(Category const & cat, std::string_view message) const;
    inline void trace(std::string_view message) const;
    inline void debug(Category const & cat, std::string_view message) const;
    inline void debug(std::string_view message) const;
    inline void info(Category const & cat, std::string_view message) const;
    inline void info(std::string_view message) const;
    inline void warning(Category const & cat, std::string_view message) const;
    inline void warning(std::string_view message) const;
    inline void error(Category const & cat, std::string_view message) const;
    inline void error(std::string_view message) const;
    inline void fatal(Category const & cat, std::string_view message) const;
    inline void fatal(std::string_view message) const;

private:
    Log * mLog;
    std::string mTag;
};


// inline members


inline bool operator==(Logger const & a, Logger const & b)
{
    return (a.mLog == nullptr || b.mLog == nullptr)
        ? (a.mLog == b.mLog)
        : (a.mLog == b.mLog && a.mTag == b.mTag);
}


inline bool operator!=(Logger const & a, Logger const & b)
{
    return !(a == b);
}


inline bool operator==(Logger const & a, std::nullptr_t b)
{
    return (a.mLog == nullptr);
}


inline bool operator!=(Logger const & a, std::nullptr_t b)
{
    return !(a == b);
}


inline bool Logger::isNull() const noexcept
{
    return mLog == nullptr;
}


inline void Logger::write(Level const & level, std::string_view message) const
{
    write(DEFAULT, level, message);
}

inline void Logger::write(std::string_view message) const
{
    write(DEFAULT, MAX, message);
}

inline void Logger::trace(Category const & cat, std::string_view message) const
{
    write(cat, TRACE, message);
}

inline void Logger::trace(std::string_view message) const
{
    write(DEFAULT, TRACE, message);
}

inline void Logger::debug(Category const & cat, std::string_view message) const
{
    write(cat, DEBUG, message);
}

inline void Logger::debug(std::string_view message) const
{
    write(DEFAULT, DEBUG, message);
}

inline void Logger::info(Category const & cat, std::string_view message) const
{
    write(cat, INFO, message);
}

inline void Logger::info(std::string_view message) const
{
    write(DEFAULT, INFO, message);
}

inline void Logger::warning(Category const & cat, std::string_view message) const
{
    write(cat, WARNING, message);
}

inline void Logger::warning(std::string_view message) const
{
    write(DEFAULT, WARNING, message);
}

inline void Logger::error(Category const & cat, std::string_view message) const
{
    write(cat, ERROR, message);
}

inline void Logger::error(std::string_view message) const
{
    write(DEFAULT, ERROR, message);
}

inline void Logger::fatal(Category const & cat, std::string_view message) const
{
    write(cat, FATAL, message);
}

inline void Logger::fatal(std::string_view message) const
{
    write(DEFAULT, FATAL, message);
}

} // namespace pdg::log

