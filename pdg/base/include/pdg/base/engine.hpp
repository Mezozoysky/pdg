#pragma once

#include <pdg/log/log.hpp>
#include <pdg/cnfg/config.hpp>

#include <memory>
#include <string>


namespace pdg::base
{


class Engine
{
public:
    Engine();
    Engine(Engine const & other) = delete;
    Engine(Engine && other) noexcept = default;
    ~Engine() = default;

    Engine & operator=(Engine const & other) = delete;
    Engine & operator=(Engine && other) = default;

    inline log::Log * getLog() noexcept;
    inline cnfg::Config * getConfig() noexcept;

private:

private:
    log::Log mLog;
    cnfg::Config mConfig;
};


// template/inline members

inline log::Log * Engine::getLog() noexcept
{
    return &mLog;
}


inline cnfg::Config * Engine::getConfig() noexcept
{
    return &mConfig;
}


} // namspace pdg::base
