#include "plugin/manager.h"

#include <memory>

manager::plugin::plugin(const checker& chk, const actor& act) 
  : chk_(chk), act_(act)
{ }

const checker& manager::plugin::get_checker(void) const 
{ 
  return chk_; 
}

const actor& manager::plugin::get_actor(void) const 
{ 
  return act_; 
}

manager::manager() { }
manager::~manager() 
{ 
  for (plugin *p : plugins_)      
    delete p;      
}

void manager::enroll(const checker& chk, const actor& act)
{
  plugins_.push_back( new plugin(chk, act) );
}

const actor *manager::lookup(const std::string& path)
{
  for (plugin *p : plugins_)
  {
    if ( p->get_checker().check(path) )
    {
      return &(p->get_actor());
    }
  }

  return nullptr;
}

manager& manager::instance(void)
{
  static std::unique_ptr<manager> ptr( new manager() );
  return *ptr;
}
