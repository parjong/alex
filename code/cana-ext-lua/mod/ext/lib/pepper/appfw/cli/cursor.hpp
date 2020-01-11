#ifndef __PEPPER_APPFW_CLI_CURSOR_H__
#define __PEPPER_APPFW_CLI_CURSOR_H__

#include <pepper/collection.hpp>

#include <string>

namespace pepper { namespace appfw { namespace cli {

  typedef pepper::collection::cursor::bean<std::string> cursor;

} } }

#endif // __PEPPER_APPFW_CLI_CURSOR_H__
