#ifndef __CLEO_STANDALONE_APP_H__
#define __CLEO_STANDALONE_APP_H__

#include "cleo/App.h"

namespace cleo
{

struct StandaloneApp : public App
{
  virtual ~StandaloneApp() = default;

  virtual int run(const Args *arg) const = 0;

  int run(const Trail *, const ID &, const Args *arg) const final;
};

} // namespace cleo

#endif // __CLEO_STANDALONE_APP_H__
