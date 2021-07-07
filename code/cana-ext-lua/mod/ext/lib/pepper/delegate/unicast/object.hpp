#ifndef __PEPPER_DELEGATE_UNICAST_OBJECT_H__
#define __PEPPER_DELEGATE_UNICAST_OBJECT_H__

#include <pepper/fun.hpp>

namespace pepper { namespace delegate { namespace unicast {

  template <typename Ret, typename... Args> class object
  {
    private:
      std::function<Ret (Args...)> _function;

    public:
      object() = default;
      ~object() = default;

    public:
      object &operator=(const std::function<Ret (Args...)> &function)
      {
        _function = function;
        return *this;
      }

    public:
      Ret operator()(Args... args) const
      {
        return _function(args...);
      }
  };

} } }

#endif
