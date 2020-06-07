#include "cleo/SelectorApp.h"

namespace
{

class ShiftedArg final : public cleo::Args
{
public:
  ShiftedArg(const Args *arg) : _arg{arg}
  {

  }

public:
  uint32_t count(void) const override { return _arg->count() - 1; }
  std::string value(uint32_t n) const override { return _arg->value(n + 1); }

private:
  const Args *_arg;
};

} // namespace

namespace cleo
{

SelectorApp::HelpMessageServiceImpl::HelpMessageServiceImpl(const SelectorApp *app, const ID &name)
  : _app{app}, _name{name}
{
  // DO NOTHING
}

void SelectorApp::HelpMessageServiceImpl::show(std::ostream &os) const
{
  _app->help(os, _name);
}

int SelectorApp::run(const Trail *cur_head, const ID &cur_id, const Args *cur_args) const 
{
  if (cur_args->count() > 0)
  {
    auto child_id = cur_args->value(0);
    ShiftedArg child_args{cur_args};
    
    auto it = _commands.find(child_id);
    if (it != _commands.end())
    {
      Trail new_head{cur_head};

      new_head.id(cur_id);        
      new_head.service<HelpMessageService>(std::make_unique<HelpMessageServiceImpl>(this, cur_id));

      return it->second->run(&new_head, child_id, &child_args);
    }
  }

  // std::cerr << "???" << std::endl;
  // std::cerr << help(name) << std::endl;
  help(std::cerr, cur_id);
  return 255;
}

void SelectorApp::help(std::ostream &os, const ID &name) const
{
  os << "USAGE: " << name << " [COMMAND]" << std::endl;
  os << std::endl;
  os << "SUPPORTED COMMANDS:" << std::endl;

  for (auto it = _commands.begin(); it != _commands.end(); ++it)
  {
    os << "  " << it->first << std::endl;
  }
}

} // namespace cleo
