#ifndef __CLEO_ATOM_APP_H__
#define __CLEO_ATOM_APP_H__

#include "cleo/App.h"

namespace cleo
{

struct AtomApp : public App
{
  virtual ~AtomApp() = default;

  virtual int run(const Args *arg) const = 0;

  int run(const Trail *, const ID &, const Args *arg) const final
  {
    return run(arg);
  }
};

} // namespace cleo

#endif // __CLEO_ATOM_APP_H__
