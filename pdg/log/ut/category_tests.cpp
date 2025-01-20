#include <catch2/catch_test_macros.hpp>

#include <pdg/log/category.hpp>


using namespace pdg::log;


TEST_CASE("pdg::log::Category basic tests", "[pdg,log]")
{
    Category yellow{"yellow"};

    REQUIRE(yellow.getName() == "yellow");

    Category yellow2{"yellow"};

    REQUIRE(yellow2.getName() == yellow.getName());
    REQUIRE(yellow2 == yellow);

    Category pink{"pink"};

    REQUIRE(pink.getName() != yellow.getName());
    REQUIRE(pink != yellow);
};

