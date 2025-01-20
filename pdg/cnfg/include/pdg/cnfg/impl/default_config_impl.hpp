#pragma once

#include <pdg/cnfg/config_impl.hpp>
#include <pdg/cnfg/impl/config_entry.hpp>
#include <map>
#include <memory>


namespace pdg::cnfg::impl
{


class DefaultConfigImpl : public ConfigImpl
{
public:
    DefaultConfigImpl();
    virtual ~DefaultConfigImpl() = default;

    inline virtual bool hasEntry(std::string const & path) const override final;

    inline virtual bool addBoolEntry(std::string && path) override final;
    inline virtual bool addBoolEntry(std::string && path, bool && defaultValue) override final;
    inline virtual bool addStringEntry(std::string && path) override final;
    inline virtual bool addStringEntry(std::string && path, std::string && defaultValue) override final;
    inline virtual bool addUInt32Entry(std::string && path) override final;
    inline virtual bool addUInt32Entry(std::string && path, std::uint32_t && defaultValue) override final;

    virtual bool hasValue(std::string const & path) const override final;
    inline virtual bool getBoolValue(std::string const & path, bool & value) const override final;
    inline virtual bool getStringValue(std::string const & path, std::string & value) const override final;
    inline virtual bool getUInt32Value(std::string const & path, std::uint32_t & value) const override final;

    virtual bool processCmdLine(std::vector<std::string> const & cmdLine,
                                std::string & configPath) override;
    virtual bool processConfigFile(std::string const & configPath) override;
    virtual bool checkEntries() const override;

    template<typename ValueT>
    ConfigEntryTyped<ValueT> * const getEntry(std::string const & path) const;

    template<typename ValueT>
    bool addEntry(std::string && path);

    template<typename ValueT>
    bool addOptionalEntry(std::string && path, ValueT && defaultValue);

    template<typename ValueT>
    bool getValue(std::string const & path, ValueT & value) const;

private:
    ConfigEntry * const getEntry(std::string const & path) const;
    bool addEntry(std::string && path, std::unique_ptr<ConfigEntry> && entry);

private:
    std::map<std::string, std::unique_ptr<ConfigEntry>> mEntries;
};


// inline/template members

inline bool DefaultConfigImpl::hasEntry(std::string const & path) const
{
    return mEntries.contains(path);
}


inline bool DefaultConfigImpl::addBoolEntry(std::string && path)
{
    return addEntry<bool>(std::move(path));
}


inline bool DefaultConfigImpl::addBoolEntry(std::string && path, bool && defaultValue)
{
    return addOptionalEntry<bool>(std::move(path), std::move(defaultValue));
}


inline bool DefaultConfigImpl::addStringEntry(std::string && path)
{
    return addEntry<std::string>(std::move(path));
}


inline bool DefaultConfigImpl::addStringEntry(std::string && path, std::string && defaultValue)
{
    return addOptionalEntry<std::string>(std::move(path), std::move(defaultValue));
}


inline bool DefaultConfigImpl::addUInt32Entry(std::string && path)
{
    return addEntry<std::string>(std::move(path));
}


inline bool DefaultConfigImpl::addUInt32Entry(std::string && path, std::uint32_t && defaultValue)
{
    return addOptionalEntry<std::uint32_t>(std::move(path), std::move(defaultValue));
}


inline bool DefaultConfigImpl::getBoolValue(std::string const & path, bool & value) const
{
    return getValue<bool>(path, value);
}


inline bool DefaultConfigImpl::getStringValue(std::string const & path, std::string & value) const
{
    return getValue<std::string>(path, value);
}


inline bool DefaultConfigImpl::getUInt32Value(std::string const & path, std::uint32_t & value) const
{
    return getValue<std::uint32_t>(path, value);
}


template<typename ValueT>
ConfigEntryTyped<ValueT> * const DefaultConfigImpl::getEntry(std::string const & path) const
{
    auto * entry = getEntry(path);
    if (entry == nullptr)
    {
        // TODO: log error
        return nullptr;
    }

    auto * entryImpl = static_cast<ConfigEntryTyped<ValueT> *>(entry);
    if (entry == nullptr)
    {
        // TODO: log error
    }

    return entryImpl;
}


template<typename ValueT>
bool DefaultConfigImpl::addEntry(std::string && path)
{
    auto entry = std::make_unique<ConfigEntryTyped<ValueT>>();
    return addEntry(std::move(path), std::move(entry));
}


template<typename ValueT>
bool DefaultConfigImpl::addOptionalEntry(std::string && path, ValueT && defaultValue)
{
    auto entry = std::make_unique<ConfigEntryTyped<ValueT>>();
    entry->setDefaultValue(std::move(defaultValue));
    return addEntry(std::move(path), std::move(entry));
}


template<typename ValueT>
bool DefaultConfigImpl::getValue(std::string const & path, ValueT & value) const
{
    ConfigEntry * const entry = getEntry(path);
    if (entry == nullptr)
    {
        // TODO: log error
        return false;
    }

    auto * entryImpl = dynamic_cast<ConfigEntryTyped<ValueT> *>(entry);
    if (entryImpl == nullptr)
    {
        // TODO: log error
        return false;
    }

    return entryImpl->getValue(value);
}


} // namespace pdg::cnfg::impl
