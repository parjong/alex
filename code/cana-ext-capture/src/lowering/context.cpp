#include "context.h"

namespace lowering {

  context::context(std::list<std::string> &arg, std::list<std::string> &out, observer &o) : _arg(arg), _out(out), _o(o)
  {
    // DO NOTHING
  }

  bool context::has_next(void) const
  {
    return _arg.size() > 0;
  }

  const std::string &context::front(void) const
  {
    return _arg.front();
  }

  void context::pop(void)
  {
    _arg.pop_front();
  }

  void context::forward(const std::string &tok)
  {
    _o.forward(_arg.front(), tok);
    _out.push_back(tok);
  }

}
