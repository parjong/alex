#ifndef __CORE_UNIT_NAME_H__
#define __CORE_UNIT_NAME_H__

#ifndef FORWARD_DECL
#include <pepper/attr.hpp>

#include <string>

namespace core { namespace unit {

  class name
  {
    public:
      pepper::attr::value::reader<std::string> string;

    public:
      name(const std::string &tag);
      ~name() = default;
  };

} } 
#else
namespace core { namespace unit {

  class name;

} }
#endif

#endif
