#ifndef __CANA_CORELIB_LOG_TEXT_FILE_H__
#define __CANA_CORELIB_LOG_TEXT_FILE_H__

#include <fstream>
#include <string>

namespace cana { namespace corelib { namespace log { namespace text {

  class file
  {
    private:
      std::ofstream _os;

    public:
      file(const std::string &name);

    public:
      ~file() = default;

    public:
      void write(const std::string &tag, const std::string &msg);
  };

} } } }

#endif
