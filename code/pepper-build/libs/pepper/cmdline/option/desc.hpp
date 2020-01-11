#ifndef __PEPPER_CMDLINE_OPTION_DESC_H__
#define __PEPPER_CMDLINE_OPTION_DESC_H__

#include <pepper/cmdline/action/desc.hpp>
#include <pepper/maybe.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace cmdline { namespace option {

  struct desc
  {
    private:
      std::shared_ptr<pepper::cmdline::action::desc> _action;

    public:
      desc &action(const std::shared_ptr<pepper::cmdline::action::desc> &action);
      const std::shared_ptr<pepper::cmdline::action::desc> &action();

    public:
      desc() = default;
      ~desc() = default;
  };

} } }

#endif
