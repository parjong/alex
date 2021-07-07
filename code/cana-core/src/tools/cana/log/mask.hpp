#ifndef __CANA_LOG_MASK_H__
#define __CANA_LOG_MASK_H__

namespace cana { namespace log {

  enum mask : unsigned int
  {
    BM_TRACE = 0x00000001,
    BM_DEBUG = 0x00000002,
    BM_INFO  = 0x00000004,
    BM_WARN  = 0x00000008,
    BM_ERROR = 0x00000010,
    BM_FATAL = 0x00000020,
  };

} }

#endif
