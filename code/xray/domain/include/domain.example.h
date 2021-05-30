#ifndef __DOMAIN_EXAMPLE_H__
#define __DOMAIN_EXAMPLE_H__

#include <xray.h>

#include <string>
#include <map>
#include <memory>
#include <vector>

struct MyEvent
{
  MyEvent(const std::string &msg) : _msg{msg}
  {

  }
  std::string _msg;
};

struct MyDomain final : public xray::EventDomain
{
private:
  MyDomain() = default;

public:
  xray::EventIndex create(const std::string &msg)
  {
    auto id = _events.size();
    _events.emplace_back(msg);
    return id;
  }

  const MyEvent &event(const xray::EventIndex &id) const { return _events.at(id); }

  std::unique_ptr<std::string> what(const xray::EventIndex &id) const override
  {
    return std::make_unique<std::string>(_events.at(id)._msg);
  }

private:
  std::vector<MyEvent> _events;

public:
  static MyDomain *get(void);
};

#endif // __DOMAIN_EXAMPLE_H__
