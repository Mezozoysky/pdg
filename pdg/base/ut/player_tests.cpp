#include <catch2/catch_test_macros.hpp>

#include <pdg/base/player.hpp>
#include <pdg/log/log.hpp>

#include <fmt/format.h>

#include <iostream>
#include <cstdint>


using namespace pdg;


class TestPlayer : public base::Player
{
public:
    TestPlayer()
    : base::Player("TestPlayer")
    {
    }

    virtual ~TestPlayer() = default;

protected:
    //virtual int perform() override
    //{
    //    auto * log = getContext().getService<log::Log>();
    //    log->trace("TestPlayer::onRun()");
    //    
    //    int error = 0;

    //    //TODO: payload

    //    log->trace(fmt::format("TestPlayer::onRun() terminated with error code {}", error));

    //    return error;
    //}
};


TEST_CASE("base::Player tests", "[base,Player]")
{
    TestPlayer player;
    REQUIRE(player.getAppName() == "TestPlayer");
    REQUIRE(player.getOrgName().empty());
    std::vector<std::string> args = {{"--set"}, {"/log/level"}, {"TRACE"},};
    int error = player.play({"./TestPlayer"}, args);
    REQUIRE(error == 0);
}

