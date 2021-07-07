#ifndef __PEPPER_APPFW_APP_SERVICE_EXITCODE_DESC_H__
#define __PEPPER_APPFW_APP_SERVICE_EXITCODE_DESC_H__

namespace pepper { namespace appfw { namespace service { namespace exitcode {

  struct desc
  {
    desc() = default;
    virtual ~desc() = default;

    virtual void set(const int &num) = 0;
  };

} } } }

#endif // __PEPPER_APPFW_APP_SERVICE_EXITCODE_DESC_H__
