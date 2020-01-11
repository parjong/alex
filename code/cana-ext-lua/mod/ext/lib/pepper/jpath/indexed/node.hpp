#ifndef __PEPPER_JPATH_INDEXED_NODE_H__
#define __PEPPER_JPATH_INDEXED_NODE_H__

#include <pepper/jpath/node.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace jpath { namespace indexed {

  class node : public jpath::node
  {
    private:
      std::shared_ptr<jpath::node> _prev;
      int _offset;

    public:
      node(const std::shared_ptr<jpath::node> &prev, int offset);
      virtual ~node() = default;

    public:
      const jpath::node &prev(void) const;
      int offset(void) const;

    public:
      virtual void accept(jpath::visitor &v) const;
  };

} } }

#endif
