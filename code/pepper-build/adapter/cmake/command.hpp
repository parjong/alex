#ifndef __PEPPERBUILD_ADAPTER_CMAKE_COMMAND_H__
#define __PEPPERBUILD_ADAPTER_CMAKE_COMMAND_H__

#include <pepper/attr.hpp>

#include <string>
#include <vector>

#include <ostream>

namespace adapter { namespace cmake {

  class command
  {
    private:
      std::string _tag;

    public:
      command(const std::string &tag);
      ~command() = default;

    public:
      pepper::attr::value::accessor<std::vector<std::string>> args;

    public:
      void dump_into(std::ostream &os) const;
  };

} }


#endif
