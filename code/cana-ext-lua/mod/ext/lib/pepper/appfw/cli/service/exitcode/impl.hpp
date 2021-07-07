#ifndef __PEPPER_APPFW_CLI_SERVICE_EXITCODE_IMPL_H__
#define __PEPPER_APPFW_CLI_SERVICE_EXITCODE_IMPL_H__

#include <pepper/appfw/service/exitcode/desc.hpp>
#include <pepper/optional.hpp>

namespace pepper { namespace appfw { namespace cli { namespace service { namespace exitcode {

  struct impl : public pepper::appfw::service::exitcode::desc
  {
    private:
      optional::object<int> &_code;

    public:
      virtual void set(const int &num);

    public:
      impl(optional::object<int> &code);
      
    public:
      virtual ~impl(void) = default;
  };

} } } } }

#endif
