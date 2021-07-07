#ifndef MODE_H__
#define MODE_H__

#include "emit/emit.h"

#include <map>

namespace mode 
{
  class action
  {
    public:
      action();
      virtual ~action();
    public:
      virtual void run(Emit& emit, int arc, char **argv) = 0;
  };

  class manager
  {
    public:
      manager() { }
      ~manager() { }
    private:
      std::map<std::string, action *> actions_;
    public:
      void add(const std::string& name, action& act);
      action *find(const std::string& name);
  };
}

#endif
