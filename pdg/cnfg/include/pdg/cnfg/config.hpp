#pragma once

#include <string>
#include <vector>


namespace pdg::cnfg
{


class ConfigImpl;


class Config
{
public:
    Config();
    Config(ConfigImpl * impl);
    virtual ~Config();

    bool init(ConfigImpl * impl);
    inline bool isInited() const noexcept;

    bool hasEntry(std::string const & path) const;

    bool addBoolEntry(std::string && path);
    bool addBoolEntry(std::string && path, bool && defaultValue);

    bool addStringEntry(std::string && path);
    bool addStringEntry(std::string && path, std::string && defaultValue);

    bool addUInt32Entry(std::string && path);
    bool addUInt32Entry(std::string && path, std::uint32_t && defaultValue);

    bool hasValue(std::string const & path) const;
    bool getBoolValue(std::string const & path, bool & value) const;
    bool getStringValue(std::string const & path, std::string & value) const;
    bool getUInt32Value(std::string const & path, std::uint32_t & value) const;

    bool process(std::vector<std::string> const & cmdLine, std::vector<std::string> const & searchPaths);

    inline bool isProcessed() const;

private:
    virtual bool findConfigFilePath(std::vector<std::string> const & searchPaths,
                            std::string & filePath) const;

private:
    ConfigImpl * mImpl;
    bool mIsProcessed;
};


// === inline/template realisations ===


inline bool Config::isInited() const noexcept
{
    return mImpl != nullptr;
}


inline bool Config::isProcessed() const
{
    return mIsProcessed;
}


} // namespace pdg::cnfg
