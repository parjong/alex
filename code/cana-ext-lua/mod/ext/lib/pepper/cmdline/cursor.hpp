#ifndef __PEPPER_CMDLINE_CURSOR_H__
#define __PEPPER_CMDLINE_CURSOR_H__

#include <pepper/collection.hpp>

#include <string>

namespace pepper { namespace cmdline {
  
  typedef pepper::collection::cursor::object<std::string> cursor;

} }

#endif
