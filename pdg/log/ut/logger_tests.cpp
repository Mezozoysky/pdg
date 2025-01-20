#include <catch2/catch_test_macros.hpp>

#include <pdg/log/log.hpp>


using namespace pdg::log;


TEST_CASE("pdg::log::Logger basic tests", "[pdg,log]")
{
    Logger sadLogger{};

    REQUIRE(sadLogger.isNull());


    Log log{};
    //log.init(new TestLoggerImpl(&log, "/"));

    Logger happyLogger{&log, "happy"};

    REQUIRE(!happyLogger.isNull());
    REQUIRE(happyLogger.getLog() == &log);
    REQUIRE(happyLogger.getTag() == "happy");

    Logger happyJr = happyLogger.getLogger("jr");

    REQUIRE(!happyJr.isNull());
    REQUIRE(happyJr.getLog() == &log);
    REQUIRE(happyJr.getTag() == "happy/jr");

    //std::vector<LogMsgData> logMsgData{};

    //Logger logger{};
    //{
    //    auto * loggerImpl = new TestLoggerImpl(&log, "zlp");
    //    loggerImpl->setMsgDataPtr(&logMsgData);
    //    logger = loggerImpl;
    //}

    //logger.write("just message");
    //REQUIRE(logMsgData.size() == 1u);
    //REQUIRE(logMsgData[0].msg == "just message");
    //REQUIRE(logMsgData[0].tag == "zlp");
    //REQUIRE(logMsgData[0].lvl == MAX);
    //REQUIRE(logMsgData[0].cat == DEFAULT);
};

