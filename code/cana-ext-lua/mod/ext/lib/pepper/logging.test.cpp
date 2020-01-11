#include <pepper/testing.hpp>
#include <pepper/logging.hpp>

COLLECTION(logging)
{
  FACT(logger_ctor)
  {
    pepper::logging::logger logger("test");
  }

  FACT(configure)
  {
    pepper::logging::configure();
  }

  FACT(usage)
  {
    pepper::logging::configure();

    pepper::logging::logger logger("test.simple");

    logger.trace("Trace from Pepper");
    logger.debug("Debug from Pepper");
    logger.info("Info from Pepper");
    logger.warn("Warn from Pepper");
    logger.error("Error from Pepper");
    logger.fatal("Fatal from Pepper");

    logger.trace("Trace ", 1);
    logger.debug("Debug ", 3, ", ", 4);
    logger.info("Info ", 3, ", ", 4);
    logger.warn("Warn ", 3, ", ", 4);
    logger.error("Error ", 3, ", ", 4);
    logger.fatal("Fatal ", 3, ", ", 4);

    pepper::logging::logger sublogger(logger, "sub");

    sublogger.trace("Trace from sublogger");
  }
}
