#ifndef __CANA_LOG_LEVEL_H__
#define __CANA_LOG_LEVEL_H__

#include "mask.hpp"

namespace cana { namespace log {

  enum level : unsigned int
  {
    LOG_NONE  = 0x00000000,
    LOG_FATAL = BM_FATAL,
    LOG_ERROR = BM_ERROR | BM_FATAL,
    LOG_WARN  = BM_WARN  | BM_ERROR | BM_FATAL,
    LOG_INFO  = BM_INFO  | BM_WARN  | BM_ERROR | BM_FATAL,
    LOG_DEBUG = BM_DEBUG | BM_INFO  | BM_WARN  | BM_ERROR | BM_FATAL,
    LOG_TRACE = BM_TRACE | BM_DEBUG | BM_INFO  | BM_WARN  | BM_ERROR | BM_FATAL,
    LOG_ALL   = 0xffffffff
  };

} }

#endif
