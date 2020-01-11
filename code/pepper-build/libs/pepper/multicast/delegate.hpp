#ifndef __PEPPER_MULTICAST_DELEGATE_H__
#define __PEPPER_MULTICAST_DELEGATE_H__

#include <pepper/functional.hpp>
#include <vector>

namespace pepper { namespace multicast {

  template <typename Ret, typename... Args> class delegate
  {
    private:
      std::vector<std::function<Ret (Args...)>> _functions;

    public:
      delegate &operator+=(const std::function<Ret (Args...)> &function)
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
      delegate() = default;
      ~delegate() = default;
  };

} } 

#endif
