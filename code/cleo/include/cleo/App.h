#ifndef __CLEO_APP_H__
#define __CLEO_APP_H__

#include "cleo/Args.h"
#include "cleo/Service.h"
#include "cleo/Trail.h"

namespace cleo
{

struct App
{
  virtual ~App() = default;

  virtual int run(const Trail *trail, const ID &id, const Args *args) const = 0;
};

} // namespace cleo

#endif // __CLEO_APP_H__
