#ifndef __PEPPER_FUN_FINALLY_H__
#define __PEPPER_FUN_FINALLY_H__

#include <functional>

namespace pepper { namespace fun {

  class finally
  {
    private:
      std::function<void (void)> _func;

    public:
      finally(const std::function<void (void)> &func) : _func{func}
      {
        // DO NOTHING
      }

    public:
      ~finally(void)
      {
        _func();
      }
  };

} }

#endif
