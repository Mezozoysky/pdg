#include <pdg/base/player.hpp>
#include <pdg/log/log.hpp>
#include <pdg/cnfg/config.hpp>
#include <pdg/cnfg/impl/default_config_impl.hpp>
#include <pdg/core/assert.hpp>

#include <fmt/format.h>

#include <SDL.h>

#include <filesystem>
namespace fs = std::filesystem;


namespace pdg::base
{


static log::Category const PDG_BASE_APP{"pdg/base/app"};


Player::Player(std::string_view appName, std::string_view orgName)
: mContext{}
, mIsStopping{false}
, mAppName{appName}
, mOrgName{orgName}
, mBasePath{}
, mPrefPath{}
{
    PDG_ASSERT(!appName.empty(), "No application name!");
}


int Player::play(int argc, char ** argv)
{
    std::string cmd{argv[0]};
    std::vector<std::string> args;
    for (int idx = 1; idx < argc; ++idx)
    {
        args.emplace_back(argv[idx]);
    }

    return play(cmd, args);
}


int Player::play(std::string const & cmd, std::vector<std::string> & args)
{
    fmt::println("PORK_DYNAMICS\nPDG v.{}", PDG_VERSION_STR);

    int error = init();

    if (!error && !isStopping())
    {
        error = setupConfig();
    }

    if (!error && !isStopping())
    {
        error = configure(args);
    }

    if (!error && !isStopping())
    {
        error = setup();
    }

    if (!error && !isStopping())
    {
        error = perform();
        if (!isStopping())
        {
            stop(); // force stop
        }
    }

    {
        int shutdownError = shutdown();
        if (!error)
        {
            error = shutdownError;
        }
    }

    return error;
}


std::string const & Player::getBasePath() const
{
#if defined(PDG_SYSTEM_ANDROID)
    PDG_ASSERT(false, "Should not be called under undroid");
#endif
    //PDG_ASSERT(isLaunched(), "!!!");
    return mBasePath;
}


std::string const & Player::getPrefPath() const
{
    //PDG_ASSERT(isLaunched(), "!!!");
    return mPrefPath;
}


bool Player::findBasePath(std::string & basePath)
{
    basePath.clear();
#if defined(PDG_SYSTEM_ANDROID)
    return true; // base path makes no sence under Android so always return true
#else
    auto * log = getContext().getLog();
    log->trace(PDG_BASE_APP, "base::Player::findBasePath()");

    char * basePathChars = SDL_GetBasePath();
    if (basePathChars == NULL)
    {
        auto errorMessage = fmt::format("Failed to obtain application base path: {}",
                                        SDL_GetError());
        log->error(PDG_BASE_APP, errorMessage);
        return false;
    }

    basePath = basePathChars;
    SDL_free(basePathChars);

    return true;
#endif
}


bool Player::findPrefPath(std::string & prefPath)
{
    auto * log = getContext().getLog();
    log->trace(PDG_BASE_APP, "base::Player::findPrefPath()");

    char * prefPathChars = SDL_GetPrefPath(getOrgName().data(), getAppName().data());
    if (prefPathChars == NULL)
    {
        auto errorMessage = fmt::format("Failed to obtain application pref path: {}",
                                        SDL_GetError());
        PDG_ASSERT(false, errorMessage.c_str());
        log->error(PDG_BASE_APP, errorMessage);
        return false;
    }

    prefPath = prefPathChars;
    SDL_free(prefPathChars);

    return true;
}


int Player::init()
{
    auto * log = getContext().getLog();
    log->trace(PDG_BASE_APP, "base::Player::onInit()");

    //auto * config = getContext().getService<cnfg::Config>();
    //if (!config->init(new cnfg::impl::DefaultConfigImpl()))
    //{
    //    PDG_ASSERT(false, "Failed to init config!");
    //    log->fatal(PDG_BASE_APP, "Failed to init config!");
    //    return -1;
    //}

    int error = SDL_InitSubSystem(SDL_INIT_TIMER);
    if (0 != error)
    {
        auto errorMessage = fmt::format("Failed to initialize SDL timer: {}", SDL_GetError());
        log->fatal(PDG_BASE_APP, errorMessage);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal error", errorMessage.data(), NULL);
        return error;
    }

    return 0;
}


int Player::setupConfig()
{
    auto * log = getContext().getLog();
    log->trace(PDG_BASE_APP, "base::Player::onSetupConfig()");

    //auto * config = getContext().getService<cnfg::Config>();
    
    return 0;
}


int Player::configure(std::vector<std::string> & args)
{
    auto * log = getContext().getLog();
    log->trace(PDG_BASE_APP, "base::Player::onConfigure()");

    //auto * config = getContext().getService<cnfg::Config>();

    return 0;
}


int Player::setup()
{
    auto * log = getContext().getLog();
    log->trace(PDG_BASE_APP, "base::Player::onSetup()");

    return 0;
}


int Player::perform()
{
    //auto * log = getContext().getLog();
    //log->trace(PDG_BASE_APP, "base::Player::perform()");

    return 0;
}


int Player::shutdown()
{
    auto * log = getContext().getLog();
    log->trace(PDG_BASE_APP, "base::Player::onShutdown()");

    SDL_QuitSubSystem(SDL_INIT_TIMER);

    return 0;
}


} // namespace pdg::base

