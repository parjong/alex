#ifndef __CLEO_TRAIL_H__
#define __CLEO_TRAIL_H__

#include "cleo/Service.h"

#include <map>
#include <memory>
#include <string>
#include <typeindex>

namespace cleo
{

using ID = std::string;

class Trail final
{
public:
  Trail() : _parent{nullptr}
  {
    // DO NOTHING
  }

public:
  Trail(const Trail *parent) : _parent{parent}
  {
    // DO NOTHING
  }

public:
  const Trail *parent(void) const { return _parent; }

private:
  const Trail *_parent = nullptr;

public:
  const ID &id(void) const { return _id; }

  Trail *id(const ID &value)
  {
    _id = value;
    return this;
  }

private:
  ID _id;

public:
  template <typename T> Trail *service(std::unique_ptr<T> &&service)
  {
    _services[typeid(T)] = std::move(service);
    return this;
  }

  template <typename T> const T *service(void) const
  {
    auto it = _services.find(typeid(T));

    if (it == _services.end())
    {
      return nullptr;
    }

    return dynamic_cast<const T *>(it->second.get());
  }

private:
  std::map<std::type_index, std::unique_ptr<Service>> _services;
};

} // namespace cleo

#endif // __CLEO_STACK_H__
