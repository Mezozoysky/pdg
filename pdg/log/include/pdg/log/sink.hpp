#pragma once

#include "log_message.hpp" // needed for MemorySink only

#include <pdg/core/ref_counted.hpp>

#include <vector>
#include <string_view>


namespace pdg::log
{


//class LogMessage;

class SinkImpl : public core::RefCounted
{
public:
    SinkImpl() = default;
    virtual ~SinkImpl() noexcept = default;

    virtual void write(LogMessage const & msg) = 0;
};

class Sink
{
public:
    Sink();
    Sink(Sink const & other);
    Sink(Sink && other);
    Sink(SinkImpl * impl);
    ~Sink();

    Sink & operator=(Sink const & other);
    Sink & operator=(Sink && other);
    Sink & operator=(SinkImpl * impl);

    friend bool operator==(Sink const & a, Sink const & b);
    friend bool operator!=(Sink const & a, Sink const & b);
    friend bool operator==(Sink const & a, std::nullptr_t b);
    friend bool operator!=(Sink const & a, std::nullptr_t b);

    inline bool isNull() const noexcept;
    inline SinkImpl * getImpl() const noexcept;

    inline void write(LogMessage const & msg) const;

private:
    SinkImpl * mImpl;
};


class ConsoleSink : public SinkImpl
{

public:
    ConsoleSink() = default;
    virtual ~ConsoleSink() = default;

    void write(LogMessage const & msg) override;
};


class FileSink : public SinkImpl
{

public:
    FileSink();
    explicit FileSink(std::string_view fileName);
    virtual ~FileSink();

    inline std::string const & getFileName() const noexcept;

    void open(std::string_view fileName);
    void close();
    inline bool isOpen() const noexcept;

    void write(LogMessage const & msg) override;

private:
    std::string mFileName;
    FILE * mFile;
};


class MemorySink : public SinkImpl
{
public:
    MemorySink() = default;
    virtual ~MemorySink() = default;

    void write(LogMessage const & msg) override;

    inline std::vector<LogMessage> const & getMessages() const noexcept;

    inline void clearMessages();

private:
    std::vector<LogMessage> mMessages;
};


// template/inline members

inline bool operator==(Sink const & a, Sink const & b)
{
    return (a.mImpl == b.mImpl);
}


inline bool operator!=(Sink const & a, Sink const & b)
{
    return !(a == b);
}


inline bool operator==(Sink const & a, std::nullptr_t b)
{
    return (a.mImpl == nullptr);
}


inline bool operator!=(Sink const & a, std::nullptr_t b)
{
    return !(a == b);
}


inline bool Sink::isNull() const noexcept
{
    return mImpl == nullptr;
}


inline SinkImpl * Sink::getImpl() const noexcept
{
    return mImpl;
}


inline void Sink::write(LogMessage const & msg) const
{
    mImpl->write(msg);
}


inline std::string const & FileSink::getFileName() const noexcept
{
    return mFileName;
}


inline bool FileSink::isOpen() const noexcept
{
    return mFile != nullptr;
}


inline std::vector<LogMessage> const & MemorySink::getMessages() const noexcept
{
    return mMessages;
}


inline void MemorySink::clearMessages()
{
    mMessages.clear();
}


} // namespace pdg::log

