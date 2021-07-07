#include <pepper/jsoncpp/path/make.hpp>
#include <pepper/jsoncpp/path/object.hpp>

namespace {

  class builder : public pepper::jpath::visitor
  {
    private:
      pepper::jsoncpp::path::object _curr;

    public:
      builder(const pepper::jpath::object &p)
      {
        p.accept(*this);
      }

    public:
      const pepper::jsoncpp::path::object &path(void)
      {
        return _curr;
      }

    public:
      virtual void visit(const pepper::jpath::root::node &)
      {
        // DO NOTHING
      }

      virtual void visit(const pepper::jpath::named::node &o)
      {
        o.prev().accept(*this);
        _curr = _curr.named(o.name());
      }

      virtual void visit(const pepper::jpath::indexed::node &o)
      {
        o.prev().accept(*this);
        _curr = _curr.indexed(o.offset());
      }
  };
}

namespace pepper { namespace jsoncpp { namespace path {

  object make(const jpath::object &p)
  {
    ::builder b{p};

    return b.path();
  }

} } }
