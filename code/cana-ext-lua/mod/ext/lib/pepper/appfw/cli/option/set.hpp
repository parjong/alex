#ifndef __PEPPER_APPFW_CLI_OPTION_SET_H__
#define __PEPPER_APPFW_CLI_OPTION_SET_H__

#include <pepper/appfw/app/option/set.hpp>
#include <pepper/bucket.hpp>

#include <map>
#include <string>

namespace pepper { namespace appfw { namespace cli { namespace option {

  class set : public pepper::appfw::app::option::set
  {
    private:
      pepper::bucket::object<std::string, pepper::appfw::app::option::desc *> &_bucket;

    public:
      virtual void enroll(const std::string &name, pepper::appfw::app::option::desc &desc );
 
    public:
      set(pepper::bucket::object<std::string, pepper::appfw::app::option::desc *> &);
      virtual ~set() = default;
  };

} } } }

#endif
