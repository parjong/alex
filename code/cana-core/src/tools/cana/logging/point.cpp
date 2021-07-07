#include "point.hpp"

namespace cana { namespace logging {

  point::point(const std::string &name)
  {
    _name   = name;
    _stream = nullptr;
    _level  = cana::log::LOG_NONE;

    cana::logging::manager::instance().attach(this);
  }

  point::~point()
  {
    cana::logging::manager::instance().detach(this);
  }

  void point::reset(void)
  {
    _stream = nullptr;
  }

  void point::ensure(void)
  {
    if (_stream != nullptr) return;

    _stream = cana::logging::manager::instance().get().make(_name);
    _level  = _stream->level();
  }

} }
