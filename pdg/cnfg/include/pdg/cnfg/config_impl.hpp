#pragma once

#include <vector>
#include <string>


namespace pdg::cnfg
{


class ConfigImpl
{
public:
    ConfigImpl() = default;
    virtual ~ConfigImpl() noexcept = default;

    virtual bool hasEntry(std::string const & path) const = 0;

    virtual bool addBoolEntry(std::string && path) = 0;
    virtual bool addBoolEntry(std::string && path, bool && defaultValue) = 0;
    virtual bool addStringEntry(std::string && path) = 0;
    virtual bool addStringEntry(std::string && path, std::string && defaultValue) = 0;
    virtual bool addUInt32Entry(std::string && path) = 0;
    virtual bool addUInt32Entry(std::string && path, std::uint32_t && defaultValue) = 0;

    virtual bool hasValue(std::string const & path) const = 0;
    virtual bool getBoolValue(std::string const & path, bool & value) const = 0;
    virtual bool getStringValue(std::string const & path, std::string & value) const = 0;
    virtual bool getUInt32Value(std::string const & path, std::uint32_t & value) const = 0;

    virtual bool processCmdLine(std::vector<std::string> const & cmdLine, std::string & configPath)
            = 0;
    virtual bool processConfigFile(std::string const & configPath) = 0;
    virtual bool checkEntries() const = 0;
};


} // namespace pdg::cnfg
