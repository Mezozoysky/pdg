#include <catch2/catch_test_macros.hpp>

#include <pdg/log/log.hpp>


using namespace pdg::log;


TEST_CASE("Basic log tests", "[pdg,log]")
{
    {
        //Log::Ptr log = Log::createPtr<TestLoggerImpl>();

        //REQUIRE(log != nullptr);
        //REQUIRE(log->isInitialized());
    }

    {
        //Log * log = Log::createRaw<TestLoggerImpl>();

        //REQUIRE(log != nullptr);
        //REQUIRE(log->isInitialized());

        //delete log;
    }

    {
        //Log log = Log::create<TestLoggerImpl>();

        //REQUIRE(log.isInitialized());
    }
    
    Log log{};
    
    //REQUIRE(log.isInitialized());

    REQUIRE(log.isCategoryEnabled(DEFAULT));

    Category forbidden{"forbidden"};

    REQUIRE(!log.isCategoryEnabled(forbidden));

    log.enableCategory(forbidden);

    REQUIRE(log.isCategoryEnabled(forbidden));

    log.disableCategory(forbidden);

    REQUIRE(!log.isCategoryEnabled(forbidden));

    REQUIRE(log.isLevelEnabled(MAX));
    REQUIRE(log.isLevelEnabled(TRACE));
    REQUIRE(log.isLevelEnabled(DEBUG));
    REQUIRE(log.isLevelEnabled(INFO));
    REQUIRE(log.isLevelEnabled(WARNING));
    REQUIRE(log.isLevelEnabled(ERROR));
    REQUIRE(log.isLevelEnabled(FATAL));

    Level notice{"NOTICE", 500};

    REQUIRE(!log.isLevelEnabled(notice));

    log.enableLevel(notice);

    REQUIRE(log.isLevelEnabled(notice));

    log.disableLevel(notice);

    REQUIRE(!log.isLevelEnabled(notice));


    REQUIRE(log.getLevel() == INFO);

    log.setLevel(TRACE);

    REQUIRE(log.getLevel() == TRACE);

    Logger logger = log.getLogger();

    REQUIRE(!logger.isNull());


    //TestLoggerImpl * loggerImpl = new TestLoggerImpl(&log, LOGGER_TAG_DELIM);
    //log.init(loggerImpl);

    //REQUIRE(log.isInitialized());

    logger = log.getLogger();

    REQUIRE(!logger.isNull());
    REQUIRE(logger.getLog() == &log);
    REQUIRE(logger.getTag() == LOGGER_TAG_DELIM);

    Logger defLogger = log.getLogger(LOGGER_TAG_DELIM);

    REQUIRE(!defLogger.isNull());
    REQUIRE(defLogger.getLog() == &log);
    REQUIRE(defLogger.getTag() == LOGGER_TAG_DELIM);
    REQUIRE(defLogger == logger);

    Logger subLogger = log.getLogger("sub");

    REQUIRE(!subLogger.isNull());
    REQUIRE(subLogger.getLog() == &log);
    REQUIRE(subLogger.getTag() == "/sub");
    REQUIRE(subLogger != defLogger);

    Logger subSubLogger = subLogger.getLogger("sub");

    REQUIRE(!subSubLogger.isNull());
    REQUIRE(subSubLogger.getLog() == &log);
    REQUIRE(subSubLogger.getTag() == "/sub/sub");
    REQUIRE(subSubLogger != subLogger);

    //std::vector<LogMsgData> msgData;
    //loggerImpl->setMsgDataPtr(&msgData);

    //log.setLevel(MAX);

    //REQUIRE(msgData.size() == 0u);

    //log.write(DEFAULT, MAX, "default max message");

    //REQUIRE(msgData.size() == 1u);
    //REQUIRE(msgData[0].cat == DEFAULT);
    //REQUIRE(msgData[0].lvl == MAX);
    //REQUIRE(msgData[0].tag == "/");
    //REQUIRE(msgData[0].msg == "default max message");

    //log.write(forbidden, MAX, "forbidden max message");

    //REQUIRE(msgData.size() == 1u);

    //log.write(DEFAULT, TRACE, "default trace message");
    //log.write(DEFAULT, DEBUG, "default debug message");
    //log.write(DEFAULT, INFO, "default info message");
    //log.write(DEFAULT, WARNING, "default warning message");
    //log.write(DEFAULT, ERROR, "default error message");
    //log.write(DEFAULT, FATAL, "default fatal message");

    //REQUIRE(msgData.size() == 1u);

    //log.setLevel(TRACE);

    //log.write(DEFAULT, MAX, "default max message");

    //log.write(DEFAULT, TRACE, "default trace message");
    //log.write(DEFAULT, DEBUG, "default debug message");
    //log.write(DEFAULT, INFO, "default info message");
    //log.write(DEFAULT, WARNING, "default warning message");
    //log.write(DEFAULT, ERROR, "default error message");
    //log.write(DEFAULT, FATAL, "default fatal message");

    //REQUIRE(msgData.size() == 8u);

    //REQUIRE(msgData[1].cat == DEFAULT);
    //REQUIRE(msgData[1].lvl == MAX);
    //REQUIRE(msgData[1].tag == "/");
    //REQUIRE(msgData[1].msg == "default max message");

    //REQUIRE(msgData[2].cat == DEFAULT);
    //REQUIRE(msgData[2].lvl == TRACE);
    //REQUIRE(msgData[2].tag == "/");
    //REQUIRE(msgData[2].msg == "default trace message");

    //REQUIRE(msgData[3].cat == DEFAULT);
    //REQUIRE(msgData[3].lvl == DEBUG);
    //REQUIRE(msgData[3].tag == "/");
    //REQUIRE(msgData[3].msg == "default debug message");

    //REQUIRE(msgData[4].cat == DEFAULT);
    //REQUIRE(msgData[4].lvl == INFO);
    //REQUIRE(msgData[4].tag == "/");
    //REQUIRE(msgData[4].msg == "default info message");

    //REQUIRE(msgData[5].cat == DEFAULT);
    //REQUIRE(msgData[5].lvl == WARNING);
    //REQUIRE(msgData[5].tag == "/");
    //REQUIRE(msgData[5].msg == "default warning message");

    //REQUIRE(msgData[6].cat == DEFAULT);
    //REQUIRE(msgData[6].lvl == ERROR);
    //REQUIRE(msgData[6].tag == "/");
    //REQUIRE(msgData[6].msg == "default error message");

    //REQUIRE(msgData[7].cat == DEFAULT);
    //REQUIRE(msgData[7].lvl == FATAL);
    //REQUIRE(msgData[7].tag == "/");
    //REQUIRE(msgData[7].msg == "default fatal message");

    //log.setLevel(INFO);

    //log.info("info message");
    //log.info(forbidden, "forbidden info message");

    //REQUIRE(msgData.size() == 9u);
    //REQUIRE(msgData[8].cat == DEFAULT);
    //REQUIRE(msgData[8].lvl == INFO);
    //REQUIRE(msgData[8].tag == "/");
    //REQUIRE(msgData[8].msg == "info message");

    //log.fatal("fatal message");
    //log.fatal(forbidden, "forbidden fatal message");

    //REQUIRE(msgData.size() == 10u);
    //REQUIRE(msgData[9].cat == DEFAULT);
    //REQUIRE(msgData[9].lvl == FATAL);
    //REQUIRE(msgData[9].tag == "/");
    //REQUIRE(msgData[9].msg == "fatal message");

    //log.debug("debug message");
    //log.debug(forbidden, "forbidden debug message");

    //REQUIRE(msgData.size() == 10u);

    //log.setLevel(DEBUG);

    //log.debug("debug message");
    //log.debug(forbidden, "forbidden debug message");

    //REQUIRE(msgData.size() == 11u);
    //REQUIRE(msgData[10].cat == DEFAULT);
    //REQUIRE(msgData[10].lvl == DEBUG);
    //REQUIRE(msgData[10].tag == "/");
    //REQUIRE(msgData[10].msg == "debug message");

    //log.info("info message");
    //log.info(forbidden, "forbidden info message");

    //REQUIRE(msgData.size() == 12u);
    //REQUIRE(msgData[11].cat == DEFAULT);
    //REQUIRE(msgData[11].lvl == INFO);
    //REQUIRE(msgData[11].tag == "/");
    //REQUIRE(msgData[11].msg == "info message");

    //log.trace("trace message");
    //log.trace(forbidden, "forbidden trace message");

    //REQUIRE(msgData.size() == 12u);
}

