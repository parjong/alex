#include "mode.h"

namespace mode
{
  action::action() { }
  action::~action() { }
}

namespace mode
{
  void manager::add(const std::string& name, action& act)
  {    
    actions_[name] = &act;
  }
  
  action *manager::find(const std::string& name)
  {
    auto it = actions_.find(name);

    if ( it == actions_.end() )
    {
      return nullptr;
    }

    return it->second;
  }

}

