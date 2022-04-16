#include <pepper/testing.hpp>
#include <pepper/jpath.hpp>

#include <sstream>

COLLECTION(jpath)
{
  class tag : public pepper::jpath::visitor
  {
    public:
      std::stringstream _ss;

    public:
      tag(const pepper::jpath::object &p)
      {
        p.accept(*this);
      }

      virtual ~tag() = default;

    public:
      std::string str(void)
      {
        return _ss.str();
      }

    public:
      virtual void visit(const pepper::jpath::root::node &)
      {
        // DO NOTHING
      }

      virtual void visit(const pepper::jpath::named::node &node)
      {
        _ss << "." << node.name();
      }

      virtual void visit(const pepper::jpath::indexed::node &node)
      {
        _ss << "@" << node.offset();
      }

    public:
      static std::string make(const pepper::jpath::object &p)
      {
        tag tag{p}; return tag.str();
      }
  };

  FACT(visitor)
  {
    auto r = pepper::jpath::make();

    EXPECT_EQ(tag::make(r), "");
    EXPECT_EQ(tag::make(r.named("first")), ".first");
    EXPECT_EQ(tag::make(r.named("first").indexed(3)), "@3");
    EXPECT_EQ(tag::make(r.named("first").indexed(3).named("second")), ".second");
  }
}
