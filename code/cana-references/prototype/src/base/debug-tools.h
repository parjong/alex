#ifndef BC_DEBUG_TOOL_H__
#define BC_DEBUG_TOOL_H__

#include <log4cxx/logger.h>

namespace debug
{
  class logger
  {
    private:
      logger();
      logger(const logger& p, const std::string& tag);
    private:
      std::string         name_;
      log4cxx::LoggerPtr  ptr_;
    public:
      log4cxx::LoggerPtr& get_ptr(void);
    public:
      const std::string& get_name(void) const;
      logger get_child(const std::string& tag_) const;
    public:
      static logger& instance();     
  };

  struct manager
  {
    static void init(void);
  };
}

#define LOG_ERROR( logger, expr ) LOG4CXX_ERROR( (logger).get_ptr(), expr );
#define LOG_INFO( logger, expr )  LOG4CXX_INFO( (logger).get_ptr(), expr );
#define LOG_DEBUG( logger, expr ) LOG4CXX_DEBUG( (logger).get_ptr(), expr );

#endif
