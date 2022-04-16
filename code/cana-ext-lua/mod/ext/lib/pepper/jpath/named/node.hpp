#ifndef __PEPPER_JPATH_NAMED_NODE_H__
#define __PEPPER_JPATH_NAMED_NODE_H__

#include <pepper/jpath/node.hpp>
#include <pepper/mem.hpp>

#include <string>

namespace pepper { namespace jpath { namespace named {

  class node : public jpath::node
  {
    private:
      std::shared_ptr<jpath::node> _prev;
      std::string _name;

    public:
      node(const std::shared_ptr<jpath::node> &, const std::string &);
      virtual ~node() = default;

    public:
      const jpath::node &prev(void) const;
      const std::string &name(void) const;

    public:
      virtual void accept(jpath::visitor &v) const;
  };

} } }

#endif
