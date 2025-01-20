#include <catch2/catch_test_macros.hpp>

#include <pdg/log/sink.hpp>
#include <pdg/log/log_message.hpp>


using namespace pdg::log;


TEST_CASE("pdg::log::Sink basic tests", "[pdg,log]")
{
    Sink sadSink{};

    REQUIRE(sadSink.isNull());

    Sink happySink{new ConsoleSink()};

    REQUIRE(!happySink.isNull());

    happySink.write(LogMessage{DEFAULT, INFO, "/zlp", "Test log message"});
};

