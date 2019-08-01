#include "cleo/StandaloneApp.h"

namespace cleo
{

int StandaloneApp::run(const Trail *, const ID &, const Args *arg) const
{
  return run(arg);
}

} // namespace cleo
