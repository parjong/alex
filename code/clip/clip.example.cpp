#include <string>
#include <memory>

//
// Framework Core
//
struct SelfManifest // TODO Find a better name
{
  void summary(const std::string &) { return; }
};

// "Param" is an untyped description of application parameters.
struct Param
{
  // VALUE,
  // CHOICE,
  // VALUES
};

struct ParamAttrs // ParamAttribSetter(?)
{
  void metavar(const std::string &) { return; }
};

struct ParamManifest
{
  ParamAttrs *add(const Param &) { return nullptr; }
};

//
//
//
struct Action
{
};

std::unique_ptr<Action> set_param(const Param &) { return nullptr; }

struct OptionalArgumentSignature
{
  void short_name(char) { return; }
  void long_name(const std::string &) { return; }
  void summary(const std::string &) { return; }
  void action(std::unique_ptr<Action> &&) { return; }
};

struct PositionalArgumentSignature
{
  void action(std::unique_ptr<Action> &&) { return; }
};

struct CmdlineManifest
{
  OptionalArgumentSignature *add_optional_argument() { return nullptr; }
  PositionalArgumentSignature *add_positional_argument() { return nullptr; }
};

// TODO Support ListParameter<T> ...   STRING -> T
// TODO Support ChoiceParameter<T> ... T <-> STRING
template <typename T> struct ValueParameter;

template <> struct ValueParameter<std::string> : public Param
{
  // String -> T
};

// App <-> Host Interface in Execution Phase
struct AppContext
{
public:
  std::string get(const ValueParameter<std::string> &) const { return ""; }

public: // Unparsed arguments
  uint32_t argc(void) const { return 0; }
  std::string argv(uint32_t n) const { return ""; }
};

struct App
{
  virtual ~App() = default;

public: // describe your self!
  virtual void describe(SelfManifest *) const { return; }
  virtual void describe(ParamManifest *) const { return; }
  virtual void describe(CmdlineManifest *) const { return; }

  virtual int process(AppContext *) const = 0;
};

struct Host
{
  int load(const App &app) const
  {
    // TODO Implement this
    return 0;
  }
};

//
// Framework Example
//
#include <iostream>

// SAMPLE - A Sample CLIP Application
//
// USAGE: SAMPLE [OPTIONS] MESSAGE
//
// SUPPORTED OPTIONS:
//   --user USER  Set user
struct MyApp final : public App
{
public: // Describe "App" itself
  void describe(SelfManifest *self) const final
  {
    //self->name("SAMPLE");
    self->summary("A Sample CLIP Application");
    // self->detail() << "..." << std::endl;
    // self->detail() << "..." << std::endl;
  }

public: // Describe the parameters that "App" needs
  ValueParameter<std::string> _user;
  ValueParameter<std::string> _message;

  void describe(ParamManifest *r) const final
  {
    // TODO Support the concept of mandatory/optional parameters
    // TODO Support the concept of "default" value
    {
      auto param = r->add(_user);
      param->metavar("USER");
    }

    {
      auto param = r->add(_message);
      param->metavar("MESAGE");
    }
  }

public: // Describe the command-line arguments that "App" accepts
  void describe(CmdlineManifest *cmdline) const final
  {
    {
      auto arg = cmdline->add_optional_argument();

      arg->long_name("user");
      arg->summary("Set user");
      arg->action(set_param(_user)); // Command-line Argument Parser will get "arity" from ill set "arity"
    }

    {
      auto arg = cmdline->add_positional_argument();

      arg->action(set_param(_message));
    }

    // cmdline->allow_unparsed_arguments();
  }

  int process(AppContext *ctx) const final
  {
    std::cout << ctx->get(_user) << std::endl;
    std::cout << ctx->get(_message) << std::endl;

    return 0;
  }
};

int main(int argc, char **argv)
{
  MyApp app;
  Host host;  
  return host.load(app);
}
