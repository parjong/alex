#ifndef __PEPPER_APPFW_CLI_ARGS_DESC_H__
#define __PEPPER_APPFW_CLI_ARGS_DESC_H__

#include <pepper/collection.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace appfw { namespace cli { namespace args {

  struct desc : public collection::data::object<std::string>
  {
    desc() = default;
    virtual ~desc() = default;
  };

} } } }

#endif
