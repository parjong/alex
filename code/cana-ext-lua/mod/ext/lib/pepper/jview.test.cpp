#include <pepper/testing.hpp>
#include <pepper/jview.hpp>

COLLECTION(jview)
{
  struct accessor : public pepper::jimage::accessor
  {
    accessor() = default;
    virtual ~accessor() = default;

    virtual void read(const pepper::jpath::object &p, const std::function<void (int)> &fn) const
    {
      // DO NOTHING
    }

    virtual void read(const pepper::jpath::object &p, const std::function<void (const std::string &)> &fn) const
    {
      // DO NOTHING
    }

    virtual void enumerate(const pepper::jpath::object &p, const std::function<void (int, const std::shared_ptr<pepper::jimage::accessor> &)> &fn) const
    {
      // DO NOTHING
    }

  };

  struct derived : public pepper::jview::obj
  {
    pepper::jview::str::fld string;
    pepper::jview::num::fld number;
    pepper::jview::seq::fld numbers;

    derived()
      : string{*this, "string"}
      , number{*this, "number"}
      , numbers{*this, "numbers"}
    {
      // DO NOTHING
    }
    virtual ~derived() = default;
  };

  FACT(read)
  {
    pepper::jimage::object image{
      pepper::mem::shared::make<accessor>()
    };

    derived d;

    d.number.read(image) << [] (int num)
    {
      // ???
    };

    d.string.read(image) << [] (const std::string &str)
    {
      // ???
    };

    d.numbers.read(image) << [] (const pepper::jpath::object &p, int ind, const pepper::jimage::object &)
    {
      // ???
    };
  }
}
