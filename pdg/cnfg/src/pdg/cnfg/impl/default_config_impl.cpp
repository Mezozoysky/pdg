#include <pdg/cnfg/impl/default_config_impl.hpp>
#include <pdg/core/assert.hpp>

#include <pugixml.hpp>

#include <fmt/format.h>

#include <sstream>


namespace pdg::cnfg::impl
{


DefaultConfigImpl::DefaultConfigImpl()
: ConfigImpl()
{
}


bool DefaultConfigImpl::hasValue(std::string const & path) const
{
    auto * entry = getEntry(path);
    return (entry == nullptr ? false : entry->hasValue());
}


bool DefaultConfigImpl::processCmdLine(std::vector<std::string> const & cmdLine,
                                       std::string & configPath)
{
    bool success = true;

    for (std::size_t idx = 0u; idx < cmdLine.size(); ++idx)
    {
        if (cmdLine[idx] == "--config")
        {
            if (idx < cmdLine.size() - 1u)
            {
                configPath = cmdLine[++idx];
            }
            else
            {
                PDG_ASSERT(false, "Command line option '--config' must have an argument!");
                // TODO: log error
                success = false;
            }
            continue;
        }

        if (cmdLine[idx] == "--set")
        {
            if (idx < cmdLine.size() - 2u)
            {
                std::string const & entryPath = cmdLine[++idx];
                std::string const & entryValStr = cmdLine[++idx];

                auto * const entry = getEntry(entryPath);
                if (!entry)
                {
                    auto errorMessage = fmt::format(
                            "Config entry specified on command line doesn't exist: '{}'",
                            entryPath);
                    PDG_ASSERT(false, errorMessage.c_str());
                    // TODO: log error
                    success = false;
                    continue;
                }
                if (!entry->setValueFromString(entryValStr))
                {
                    auto errorMessage
                            = fmt::format("Config entry specified on command line failed to "
                                          "set value from string '{}': '{}'",
                                          entryValStr,
                                          entryPath);
                    PDG_ASSERT(false, errorMessage.c_str());
                    // TODO: log error
                    success = false;
                    continue;
                }
            }
        }

    } // for

    return success;
}


bool DefaultConfigImpl::processConfigFile(std::string const & configPath)
{
    pugi::xml_document doc;
    {
        auto loadResult = doc.load_file(configPath.c_str());
        if (loadResult.status != pugi::xml_parse_status::status_ok)
        {
            // TODO: log error
            return false;
        }
    }

    if (doc.empty())
    {
        // TODO: log error
        return false;
    }

    auto rootNode = doc.child("config");
    if (rootNode.empty())
    {
        // TODO: log error
        return true;
    }

    for (auto const & [path, entry] : mEntries)
    {
        if (entry->hasObtainedValue())
        {
            continue;
        }

        std::string xpath(++path.begin(), path.end());
        auto xnodes = rootNode.select_nodes(xpath.c_str());
        if (xnodes.empty())
        {
            if (!entry->hasDefaultValue())
            {
            // TODO: log error
            }
            continue;
        }

        pugi::xml_node node;

        if (xnodes.size() > 1u)
        {
            // TODO: log error
            node = xnodes[xnodes.size() - 1u].node();
        }
        else
        {
            node = xnodes.first().node();
        }

        if (node.empty())
        {
            auto errorMessage = fmt::format("Config entry xml node is empty: '{}'", path);
            PDG_ASSERT(false, errorMessage.c_str());
            // TODO: log error
            continue;
        }

        std::string valueStr = node.text().get();
        if (valueStr.empty())
        {
            // TODO: log error
            continue;
        }

        entry->setValueFromString(valueStr);
    }

    return true;
}


bool DefaultConfigImpl::checkEntries() const
{
    std::vector<std::string_view> emptyEntries;
    for (auto const & [path, entry] : mEntries)
    {
        if (!entry->hasValue())
        {
            emptyEntries.emplace_back(path);
        }
    }

    if (!emptyEntries.empty())
    {
        //auto errorMessage = fmt::format("{} config entries are unconfigured: {}", emptyEntries.size(), emptyEntries);
        //PDG_ASSERT(false, errorMessage.c_str());
        std::ostringstream oss;
        oss << emptyEntries.size() << " config entries are unconfigured: [";
        for (std::size_t idx = 0u; idx < emptyEntries.size(); ++idx)
        {
            if (idx != 0u)
            {
                oss << ", ";
            }
            oss << '\'' << emptyEntries[idx] << '\'';
        }
        oss << "]";
        PDG_ASSERT(false, oss.str().c_str());
        // TODO: log error
        return false;
    }

    return true;
}


ConfigEntry * const DefaultConfigImpl::getEntry(std::string const & path) const
{
    auto const entryIt = mEntries.find(path);
    if (entryIt == mEntries.end())
    {
        // TODO: log error
        return nullptr;
    }
    return entryIt->second.get();
}


bool DefaultConfigImpl::addEntry(std::string && path, std::unique_ptr<ConfigEntry> && entry)
{
        PDG_ASSERT(!path.empty(), "Attempt to add config entry by empty path!");
        if (path.empty())
        {
            // TODO log error
            return false;
        }

        if (entry == nullptr)
        {
            auto errorMessage = fmt::format("Attempt to add null as config entry: '{}'", path);
            PDG_ASSERT(false, errorMessage.c_str());
            // TODO: log error
            return false;
        }

        PDG_ASSERT(path.starts_with("/"), "Entry path must be absolute");
        if (!path.starts_with("/"))
        {
            path = "/" + path;
        }

        if (hasEntry(path))
        {
            auto errorMessage = fmt::format("Attempt to add config entry repeatedly: '{}'", path);
            PDG_ASSERT(false, errorMessage.c_str());
            // TODO: log error
            return false;
        }

        mEntries.insert(std::make_pair(std::move(path), std::move(entry)));

        return true;
}


} // namespace pdg::cnfg::impl
