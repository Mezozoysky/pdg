#include <pdg/log/sink.hpp>
#include <pdg/log/log_message.hpp>

#include <pdg/core/assert.hpp>

#include <fmt/format.h>

#include <cstdio>


namespace pdg::log
{


Sink::Sink()
: mImpl{nullptr}
{
}


Sink::Sink(Sink const & other)
: mImpl{other.mImpl}
{
    if (mImpl)
    {
        mImpl->incRefCount();
    }
}


Sink::Sink(Sink && other)
: mImpl{std::move(other.mImpl)}
{
    other.mImpl = nullptr;
}


Sink::Sink(SinkImpl * impl)
: mImpl{impl}
{
    PDG_ASSERT(mImpl != nullptr, "Impl must not be null!");
    mImpl->incRefCount();
}


Sink::~Sink()
{
    if (mImpl)
    {
        mImpl->decRefCount();
    }
}


Sink & Sink::operator=(Sink const & other)
{
    if (mImpl)
    {
        mImpl->decRefCount();
    }
    mImpl = other.mImpl;
    if (mImpl)
    {
        mImpl->incRefCount();
    }
    return *this;
}


Sink & Sink::operator=(Sink && other)
{
    if (mImpl)
    {
        mImpl->decRefCount();
    }
    mImpl = std::move(other.mImpl);
    other.mImpl = nullptr;
    return *this;
}


Sink & Sink::operator=(SinkImpl * impl)
{
    if (mImpl)
    {
        mImpl->decRefCount();
    }
    mImpl = impl;
    if (mImpl)
    {
        mImpl->incRefCount();
    }
    return *this;
}


void ConsoleSink::write(LogMessage const & msg)
{
    fmt::println("{} {}[{}]{}: {}",
                 /*timeStamp*/ "TIMESTAMP",
                 msg.level.getName(),
                 msg.category.getName(),
                 msg.tag,
                 msg.message);
}


FileSink::FileSink()
: mFileName{}
, mFile{nullptr}
{
}


FileSink::FileSink(std::string_view fileName)
: mFileName{fileName}
, mFile{nullptr}
{
    open(fileName);
}


FileSink::~FileSink()
{
    close();
}


void FileSink::open(std::string_view fileName)
{

    PDG_ASSERT(!mFileName.empty(), "Attempt to create FileSink with empty fileName");
    if (mFileName.empty())
    {
        return;
    }

    mFile = fopen(mFileName.c_str(), "w");
    PDG_ASSERT(isOpen(),
                fmt::format("Failed to open for writing log file: '{}'", mFileName).c_str());
}


void FileSink::close()
{
    if (isOpen())
    {
        fflush(mFile);
        fclose(mFile);
        mFile = nullptr;
    }
}


void FileSink::write(LogMessage const & msg)
{
    PDG_ASSERT(isOpen(), "");
    if (!isOpen())
    {
        return;
    }
    fmt::println(mFile,
                 "{} {}[{}]{}: {}",
                 /*timeStamp*/ "TIMESTAMP",
                 msg.level.getName(),
                 msg.category.getName(),
                 msg.tag,
                 msg.message);
}


void MemorySink::write(LogMessage const & msg)
{
    mMessages.emplace_back(msg);
}


} // namespace pdg::log

