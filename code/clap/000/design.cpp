#include <cstdint>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#if 0
The following code is not allowed in C++

struct A
{
  struct B
  {
    B();
  }

  B::B()
  {
    // ...
  }
};
#endif

namespace clap
{

struct Option
{
  char _short_name = '\0';
  std::string _long_name;

  bool _required = false;

  // TODO Record "the number of arguments (arity)"
  // TODO Record "the type of each arguments"
  // TODO Support repeated options
};

struct OptionBuilder
{
  OptionBuilder &name(char c) { return (*this); }
  OptionBuilder &required(void) { return (*this); }
};

class App
{
public:
  struct Arg {
    Option _opt;
  };

  // To distinguish return type
  struct StrArg : public Arg { };

public:
  struct Session
  {
    virtual std::string get(const StrArg &) const = 0;
  };

public:
  virtual ~App() = default;

private:
  // Tries to support static initialization, but it does not work
  std::vector<const Option *> _options;

public:
  const std::vector<const Option *> &options(void) const { return _options; }

protected:
  OptionBuilder option(Arg *) { return OptionBuilder{}; }

public:
  virtual int entry(const Session *) const = 0;
};

// Standalone CLI Application
template <typename T> struct BasicApp : public App
{
  virtual ~BasicApp() = default;
};

} // namespace clap

//
// How to run a clap::App
//
struct AppSession final : clap::App::Session
{
  // TODO Use "multimap" (to support repeated arguments)
  std::map<int /* Option Index */, std::string> args;

  std::string get(const clap::App::StrArg &opt) const final
  {
    return "";
  }
};

namespace clap
{

int run(const clap::App &app, int argc, char **argv)
{
  std::cout << "Hey" << std::endl;
  return 0;
#if 0
  AppSession ctx;

  std::map<std::string, std::function<void (const std::string &arg)>> fns;

  // Build Parsing Rules (except help)
  for (const auto &opt : app.options())
  {
    // TODO Get "arity" from type
    std::cout << opt->_name << std::endl;

    auto index = opt->index;

    fns["--" + opt->_name] = [index, &ctx] (const std::string &arg) {
      ctx.args[index] = arg;
    };
  }

  int pos = 1;

  while (pos < argc)
  {
    // TODO Show error message when optarg is missing
    // TODO Support "-h" or "--help"
    auto tok = argv[pos++];
    auto arg = argv[pos++];

    auto f = fns.at(tok);

    f(arg);
  }

  // TODO Validate context
  // REQUIRED, BUT MISSING
  // ...
  return app.entry(&ctx);
#endif
}

} // namespace clap

// AppSession { App + Name }

void show_help(const clap::App &app)
{
  std::cout << "USAGE: <...> [OPTIONS] ..." << std::endl;
  std::cout << std::endl;
  std::cout << "SUPPORTED OPTIONS:" << std::endl;
#if 0
  for (const auto &opt : app._options)
  {
    std::cout << "  " << opt->_name << " <STRING>" << std::endl;
  }
#endif
}

#define CLAP_MAIN(APP_CLASS)              \
  int main(int argc, char **argv)         \
  {                                       \
    APP_CLASS app;                        \
    return ::clap::run(app, argc, argv);  \
  }

#include "example.inl"
