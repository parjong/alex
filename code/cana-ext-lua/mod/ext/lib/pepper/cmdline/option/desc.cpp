#include <pepper/cmdline/option/desc.hpp>

namespace pepper { namespace cmdline { namespace option {

  desc &desc::action(const std::shared_ptr<pepper::cmdline::action::desc> &action)
  {
    _action = action;
    return *this;
  }

  const std::shared_ptr<pepper::cmdline::action::desc> &desc::action()
  {
    return _action;
  }

} } }
