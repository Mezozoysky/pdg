#include <pdg/cnfg/config.hpp>
#include <pdg/cnfg/config_impl.hpp>
#include <pdg/core/assert.hpp>

#include <filesystem>
namespace fs = std::filesystem;


namespace pdg::cnfg
{


Config::Config()
: mImpl{nullptr}
, mIsProcessed{false}
{
}


Config::Config(ConfigImpl * impl)
: mImpl{nullptr}
, mIsProcessed{false}
{
    init(impl);
}


Config::~Config()
{
    if (!mImpl)
    {
        return;
    }

    delete mImpl;
    mImpl = nullptr;
}


bool Config::init(ConfigImpl * impl)
{
    PDG_ASSERT(!isInited(), "Trying to init Config repeatedly!");
    if (isInited())
    {
        return false;
    }

    PDG_ASSERT(impl, "Impl is null!");
    if (!impl)
    {
        return false;
    }

    mImpl = impl;
    return true;
}


bool Config::hasEntry(std::string const & path) const
{
    PDG_ASSERT(isInited(), "hasEntry() should not be called before init()");
    if (!isInited())
    {
        // TODO: log error
        return false;
    }

    return mImpl->hasEntry(path);
}


bool Config::addBoolEntry(std::string && path)
{
    PDG_ASSERT(isInited(), "addBoolEntry() should not be called before init()");
    if (isInited())
    {
        // TODO: log error
        return false;
    }

    return mImpl->addBoolEntry(std::move(path));
}


bool Config::addBoolEntry(std::string && path, bool && defaultValue)
{
    PDG_ASSERT(isInited(), "addBoolEntry() should not be called before init()");
    if (!isInited())
    {
        // TODO: log error
        return false;
    }

    return mImpl->addBoolEntry(std::move(path), std::move(defaultValue));
}


bool Config::addStringEntry(std::string && path)
{
    PDG_ASSERT(isInited(), "addStringEntry() should not be called before init()");
    if (!isInited())
    {
        // TODO: log error
        return false;
    }

    return mImpl->addStringEntry(std::move(path));
}


bool Config::addStringEntry(std::string && path, std::string && defaultValue)
{
    PDG_ASSERT(isInited(), "addStringEntry() should not be called before init()");
    if (!isInited())
    {
        // TODO: log error
        return false;
    }

    return mImpl->addStringEntry(std::move(path), std::move(defaultValue));
}


bool Config::addUInt32Entry(std::string && path)
{
    PDG_ASSERT(isInited(), "addStringEntry() should not be called before init()");
    if (!isInited())
    {
        // TODO: log error
        return false;
    }

    return mImpl->addUInt32Entry(std::move(path));
}


bool Config::addUInt32Entry(std::string && path, std::uint32_t && defaultValue)
{
    PDG_ASSERT(isInited(), "addStringEntry() should not be called before init()");
    if (!isInited())
    {
        // TODO: log error
        return false;
    }

    return mImpl->addUInt32Entry(std::move(path), std::move(defaultValue));
}


bool Config::hasValue(std::string const & path) const
{
    PDG_ASSERT(isInited(), "hasValue() should not be called before init()");
    if (!isInited())
    {
        // TODO: log error
        return false;
    }

    return mImpl->hasValue(path);
}


bool Config::getBoolValue(std::string const & path, bool & value) const
{
    PDG_ASSERT(isInited(), "getBoolValue() should not be called before init()");
    if (!isInited())
    {
        // TODO: log error
        return false;
    }

    return mImpl->getBoolValue(path, value);
}


bool Config::getStringValue(std::string const & path, std::string & value) const
{
    PDG_ASSERT(isInited(), "getStringValue() should not be called before init()");
    if (!isInited())
    {
        // TODO: log error
        return false;
    }

    return mImpl->getStringValue(path, value);
}


bool Config::getUInt32Value(std::string const & path, std::uint32_t & value) const
{
    PDG_ASSERT(isInited(), "getBoolValue() should not be called before init()");
    if (!isInited())
    {
        // TODO: log error
        return false;
    }

    return mImpl->getUInt32Value(path, value);
}


bool Config::process(std::vector<std::string> const & cmdLine, std::vector<std::string> const & searchPaths)
{
    PDG_ASSERT(isInited(), "process() should not be called before init()");
    if (!isInited())
    {
        // TODO: log error
        return false;
    }

    std::string configFilePath;
    if (!cmdLine.empty())
    {
        mImpl->processCmdLine(cmdLine, configFilePath);
    }

    if (configFilePath.empty())
    {
        findConfigFilePath(searchPaths, configFilePath);
    }
    else
    {
        fs::path absPath = configFilePath;
        absPath = absPath.lexically_normal();
        if (!absPath.is_absolute())
        {
            absPath = fs::absolute(absPath);
        }
        configFilePath = absPath.string();
    }

    if (!configFilePath.empty())
    {
        mImpl->processConfigFile(configFilePath);
    }

    mIsProcessed = true;

    return mImpl->checkEntries();
}


bool Config::findConfigFilePath(std::vector<std::string> const & searchPaths,
                                std::string & filePath) const
{
    auto checkPath = [](std::string const & pathStr) -> bool
    {
        fs::path path(pathStr);
        if (fs::exists(path) and (fs::is_regular_file(path) or fs::is_symlink(path)))
        {
            return true;
        }

        return false;
    };

    bool success = false;
    for (auto const & path : searchPaths)
    {
        if (checkPath(path))
        {
            filePath = path;
            success = true;
            break;
        }
    }

    return success;
}


} // namespace pdg::cnfg
