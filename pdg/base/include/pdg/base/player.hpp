#pragma once

#include <pdg/base/engine.hpp>

#include <vector>
#include <string_view>
#include <optional>


namespace pdg::base
{


class Player
{
public:
    explicit Player(std::string_view appName, std::string_view orgName = "");
    virtual ~Player() = default;

    inline Engine & getContext() noexcept;

    int play(int argc, char ** argv);
    int play(std::string const & cmd, std::vector<std::string> & args);

    inline void stop() noexcept;
    inline bool isStopping() const noexcept;

    inline std::string const & getAppName() const noexcept;
    inline std::string const & getOrgName() const noexcept;

    std::string const & getBasePath() const;
    std::string const & getPrefPath() const;

protected:
    virtual bool findBasePath(std::string & basePath);
    virtual bool findPrefPath(std::string & prefPath);

    virtual int onInit()
    {
        return 0;
    }
    virtual int onSetupConfig()
    {
        return 0;
    }
    virtual int onConfigure(std::vector<std::string> & args)
    {
        return 0;
    }
    virtual int onSetup()
    {
        return 0;
    }
    //virtual int onRun() { return 0; }
    virtual int onShutdown()
    {
        return 0;
    }

private:
    int init();
    int setupConfig();
    int configure(std::vector<std::string> & args);
    int setup();
    int perform();
    int shutdown();

private:
    Engine mContext;
    bool mIsStopping;

    std::string mAppName;
    std::string mOrgName;

    std::string mBasePath;
    std::string mPrefPath;
};


// inline members

inline Engine & Player::getContext() noexcept
{
    return mContext;
}


inline void Player::stop() noexcept
{
    mIsStopping = true;
}


inline bool Player::isStopping() const noexcept
{
    return mIsStopping;
}


inline std::string const & Player::getAppName() const noexcept
{
    return mAppName;
}


inline std::string const & Player::getOrgName() const noexcept
{
    return mOrgName;
}


} // namespace pdg::base

