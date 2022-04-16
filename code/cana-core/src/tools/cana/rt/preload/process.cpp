#include "process.hpp"

namespace cana { namespace rt { namespace preload {

  process::process(const preload::record &record) : _record(record)
  {
    // DO NOTHING
  }

  const std::string &process::image(void) const
  {
    return _record.image();
  }

  const cana::proc::arg &process::arg(void) const
  {
    return _record.arg();
  }

  const cana::proc::env &process::env(void) const
  {
    return _record.env();
  }

} } }
