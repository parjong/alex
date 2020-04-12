#include <map>
#include <memory>
#include <vector>
#include <string>
#include <iostream>

namespace isa
{

//
// Untyped Core Infrastructure
//
struct Ins
{
  struct Fld
  {
    std::string name;
  };

  std::string name;
  std::vector<std::unique_ptr<Fld>> fields;
};

//
// 
//
struct Spec // Context?
{
  std::string desc;
  std::map<char *, std::unique_ptr<Ins>> _content;

  std::vector<Ins *> all(void)
  {
    std::vector<Ins *> res;
    
    for (auto it = _content.begin(); it != _content.end(); ++it)
    {
      res.emplace_back(it->second.get());
    }

    return res;
  }

  Ins *resolve(char *c)
  {
    if (_content.find(c) == _content.end())
    {
      _content[c] = std::make_unique<Ins>();
    }

    return _content.at(c).get();
  }

  static Spec &get(void)
  {
    static Spec s;
    return s;
  }
};

template <typename T> struct InsDecl
{
public:
  InsDecl()
  {
    _ins = Spec::get().resolve(&T::ID);
  }

public:
  struct SignedField
  {
    SignedField(const std::string &name)
    {
      auto ins = Spec::get().resolve(&T::ID);

      Ins::Fld *_fld = nullptr;

      for (const auto &fld : ins->fields)
      {
        if (fld->name == name)
        {
          _fld = fld.get();
          break;
        }
      }

      if (_fld == nullptr)
      {
        auto p = std::make_unique<Ins::Fld>();
        p->name = name;
        _fld = p.get();
        ins->fields.emplace_back(std::move(p));
      }

      // DO NOTHING
    }
  };

protected:
  void name(const std::string &v) { _ins->name = v; }

private:
  Ins *_ins = nullptr;
};

//
//
//
struct InsA : InsDecl<InsA>
{
  static char ID;

  InsA()
  {
    name("A");
  }

  SignedField X{"A"};
};

char InsA::ID = 0;

InsA A;

} // namespace

int main(int argc, char **argv)
{

  // get(ins, A.X);
  // ref(ins, A.X) = 4;

  for (auto ins : isa::Spec::get().all())
  {
    std::cout << "Instruction " << ins->name << std::endl;
    for (const auto &fld : ins->fields)
    {
      std::cout << "  Field " << fld->name << std::endl;
    }
  }

  isa::A.X;

  return 0;
}
