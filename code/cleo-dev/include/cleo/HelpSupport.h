#ifndef __CLEO_HELP_SUPPORT_H__
#define __CLEO_HELP_SUPPORT_H__

#include "cleo/App.h"
#include "cleo/Service.h"

#include <iostream>

namespace cleo
{

struct HelpMessageService : public Service
{
  virtual ~HelpMessageService() = default;

  virtual void show(std::ostream &os) const = 0;
};

// This app works only when "parent" exposes "HelpMessageService"
struct HelpCommand final : public App
{
  int run(const Trail *trail, const ID &, const Args *) const final
  {    
    trail->service<HelpMessageService>()->show(std::cout);
    return 0;
  }
};

} // namespace cleo

#endif // __CLEO_HELP_SUPPORT_H__
