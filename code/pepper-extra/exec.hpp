#ifndef __PEPPER_EXEC_H__
#define __PEPPER_EXEC_H__

#include <string>
#include <vector>

#include "pepper/logging/logger.hpp"

namespace pepper { namespace exec {

  class command
  {
    private:
      static pepper::logging::logger _log;

    public:
      command(const std::string &exe);
      ~command() = default;
        
    private:
      std::string _exe;

    private:
      std::vector<std::string> _args;
    public:
      void append(const std::string &arg);

    public:
      bool run(void) const;
  };

} } 

#endif
