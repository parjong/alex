#include "nni/core/Session.h"
#include "nni/core/Action.h"
#include "nni/core/Arguments.h"

#include <map>
#include <vector>
#include <string>

#include <cassert>

#include <dlfcn.h>

class VectorArguments : public Arguments
{
public:
  uint32_t size(void) const override { return _args.size(); }
  const char *at(uint32_t n) const override { return _args.at(n).c_str(); }

public:
  void append(const std::string &arg) { _args.emplace_back(arg); }

private:
  std::vector<std::string> _args;
};

class BackendSection
{
public:
  BackendSection(const std::string &path) : _path{path}
  {
    // DO NOTHING
  }

public:
  const std::string &path(void) const { return _path; }
  const Arguments &args(void) const { return _args; }

public:
  void append(const std::string &arg) { _args.append(arg); }

private:
  const std::string _path;
  VectorArguments _args;
};

class Section
{
public:
  Section(const std::string &path) : _path{path}
  {
    // DO NOTHING
  }

public:
  const std::string &path(void) const { return _path; }
  const Arguments &args(void) const { return _args; }

public:
  void append(const std::string &arg) { _args.append(arg); }

private:
  const std::string _path;
  VectorArguments _args;
};

int main(int argc, char **argv)
{
  std::unique_ptr<BackendSection> backend_section;
  std::vector<std::unique_ptr<Section>> pre_sections;
  std::vector<std::unique_ptr<Section>> post_sections;

  std::map<std::string, std::function<void (const std::string &)>> optparse;

  optparse["--backend"] = [&] (const std::string &arg)
  {
    backend_section = std::make_unique<BackendSection>(arg);
  };

  optparse["--backend-arg"] = [&] (const std::string &arg)
  {
    assert(backend_section != nullptr);
    backend_section->append(arg);
  };

  optparse["--pre"] = [&] (const std::string &arg)
  {
    pre_sections.emplace_back(std::make_unique<Section>(arg));
  };

  optparse["--pre-arg"] = [&] (const std::string &arg)
  {
    pre_sections.back()->append(arg);
  };

  optparse["--post"] = [&] (const std::string &arg)
  {
    post_sections.emplace_back(std::make_unique<Section>(arg));
  };

  optparse["--post-arg"] = [&] (const std::string &arg)
  {
    post_sections.back()->append(arg);
  };

  for (int n = 1; n < argc; n += 2)
  {
    const auto &fn = optparse.at(argv[n]);
    fn(argv[n + 1]);
  }

  assert(backend_section != nullptr);

  std::unique_ptr<Session> sess;
  std::vector<std::unique_ptr<Action>> pre_actions;
  std::vector<std::unique_ptr<Action>> post_actions;

  {
    typedef std::unique_ptr<Session> (*SessionFactoryFunc)(const Arguments &);

    void *handle = dlopen((*backend_section).path().c_str(), RTLD_NOW | RTLD_GLOBAL);
    SessionFactoryFunc make_session = reinterpret_cast<SessionFactoryFunc>(dlsym(handle, "make_session"));

    sess = make_session(backend_section->args());
  }

  auto make_action = [] (const Section &section)
  {
    typedef std::unique_ptr<Action> (*EntryFunc)(const Arguments &);

    void *handle = dlopen(section.path().c_str(), RTLD_NOW | RTLD_GLOBAL);
    EntryFunc entry = reinterpret_cast<EntryFunc>(dlsym(handle, "make_action"));

    return std::move(entry(section.args()));
  };

  for (const auto &pre_section : pre_sections)
  {
    pre_actions.emplace_back(make_action(*pre_section));
  }

  for (const auto &post_section : post_sections)
  {
    post_actions.emplace_back(make_action(*post_section));
  }

  sess->prepare([&] (State &s) {
    for (const auto &pre_action : pre_actions)
    {
      pre_action->run(s);
    }
  });
  sess->invoke();
  sess->teardown([&] (State &s) {
    for (const auto &post_action : post_actions)
    {
      post_action->run(s);
    }
  });

  return 0;
}
