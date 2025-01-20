#include <catch2/catch_test_macros.hpp>

#include <pdg/core/fragile_bool.hpp>


using namespace pdg::core;


TEST_CASE("FragileBool basic tests", "[core,FragileBool]")
{
    FragileBool<true> fTrue;
    REQUIRE(fTrue);
    fTrue = true;
    REQUIRE(fTrue);
    fTrue = false;
    REQUIRE(!fTrue);
    fTrue = true;
    REQUIRE(!fTrue);


    FragileBool<false> fFalse;
    REQUIRE(!fFalse);
    fFalse = false;
    REQUIRE(!fFalse);
    fFalse = true;
    REQUIRE(fFalse);
    fFalse = false;
    REQUIRE(fFalse);
}
