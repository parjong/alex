#ifndef __PEPPER_CMDLINE_READER_H__
#define __PEPPER_CMDLINE_READER_H__

#include <pepper/collection.hpp>

#include <string>

namespace pepper { namespace cmdline {
  
  typedef pepper::collection::reader<std::string> reader;

} }

#endif
