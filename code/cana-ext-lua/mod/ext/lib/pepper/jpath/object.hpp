#ifndef __PEPPER_JPATH_OBJECT_H__
#define __PEPPER_JPATH_OBJECT_H__

#include <pepper/jpath/node.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace jpath {

  class object
  {
    private:
      std::shared_ptr<jpath::node> _node;

    public:
      object();
      object(const std::shared_ptr<node> &node);
      object(const object &o);

    public:
      object indexed(int index) const;
      object named(const std::string &name) const;

    public:
      void accept(jpath::visitor &v) const;
  };

  object make(void);

} }

#endif
