#ifndef __CLI_SELECTOR_APP_H__
#define __CLI_SELECTOR_APP_H__

#include "cleo/App.h"
#include "cleo/HelpSupport.h"

#include <map>
#include <memory>
#include <ostream>

namespace cleo
{

// app.command("...").desc(...).entry(...)
class SelectorApp final : public App
{
public:
  class CommandBuilder final
  {
  public:
    CommandBuilder(SelectorApp *app, const std::string &key)
        : _app{app}, _key{key}
    {
      // DO NOTHING
    }

  public:
    CommandBuilder &entry(std::unique_ptr<App> &&app)
    {
      (*_app)._commands.emplace(_key, std::move(app));
      return (*this);
    }

    template <typename AppImpl, typename... Args>
    CommandBuilder &entry(Args&&... args)
    {
      return entry(std::unique_ptr<AppImpl>(new AppImpl{std::forward<Args>(args)...}));
    }

  private:
    SelectorApp *_app;
    std::string _key;
  };

public:
  int run(const Trail *, const ID &, const Args *) const final;

public:
  CommandBuilder command(const std::string &key)
  {
    return CommandBuilder{this, key};
  }

private:
  class HelpMessageServiceImpl final : public HelpMessageService
  {
  public:
    HelpMessageServiceImpl(const SelectorApp *, const ID &);
  
  public:
    void show(std::ostream &os) const final;

  private:
    const SelectorApp *_app;
    const ID _name;
  };

private:
  void help(std::ostream &os, const ID &name) const;

private:
  std::map<std::string, std::unique_ptr<App>> _commands;
};

} // namespace cleo

#endif // __CLI_SELECTOR_APP_H__
