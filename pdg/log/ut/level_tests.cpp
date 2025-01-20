#include <catch2/catch_test_macros.hpp>

#include <pdg/log/level.hpp>


using namespace pdg::log;


TEST_CASE("pdg::log::Level basic tests", "[pdg,log]")
{
    Level danger{"danger", 1500};

    REQUIRE(danger.getName() == "danger");
    REQUIRE(danger.getPriority() == 1500);

    Level danger2{"danger", 1500};

    REQUIRE(danger2.getName() == danger.getName());
    REQUIRE(danger2.getPriority() == danger.getPriority());
    REQUIRE(danger2 == danger);

    Level notSo{"not_so_danger", 1000};

    REQUIRE(notSo.getName() != danger.getName());
    REQUIRE(notSo.getPriority() != danger.getPriority());
    REQUIRE(notSo != danger);
    REQUIRE(notSo < danger);
    REQUIRE(danger > notSo);

    Level nameless{"", -10000};

    REQUIRE(nameless.getName().empty());
    REQUIRE(nameless.getPriority() == -10000);
    REQUIRE(nameless < danger);
    REQUIRE(nameless < notSo);
    REQUIRE(nameless != notSo);
};

