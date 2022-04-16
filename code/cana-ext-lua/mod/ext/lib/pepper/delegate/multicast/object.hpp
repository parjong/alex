#ifndef __PEPPER_DELEGATE_MULTICAST_OBJECT_H__
#define __PEPPER_DELEGATE_MULTICAST_OBJECT_H__

#include <pepper/fun.hpp>
#include <vector>

namespace pepper { namespace delegate { namespace multicast {

  template <typename Ret, typename... Args> class object
  {
    private:
      std::vector<std::function<Ret (Args...)>> _functions;

    public:
      object &operator+=(const std::function<Ret (Args...)> &function)
      {
        _functions.emplace_back(function);
        return *this;
      }

    public:
      std::vector<Ret> operator()(Args... args) const
      {
        std::vector<Ret> res;

        for (auto &function : _functions)
        {
          res.emplace_back( function(args...) );
        }

        return res;
      }

    public:
      object() = default;
      ~object() = default;
  };

} } }

#endif
