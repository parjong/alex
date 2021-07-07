#ifndef __PEPPER_JSON_OBJECT_VALUE_H__
#define __PEPPER_JSON_OBJECT_VALUE_H__

#include "pepper/json/field/base.forward.hpp"

#include <vector>
#include <functional>

namespace pepper { namespace json {

  struct meta
  {
    public:
      meta() = default;
      ~meta() = default;

    private:
      std::vector<field *> _fields;
    public:
      virtual void add(field &value);

    public:
      void iter(std::function<void (field &)> fn) const;
  };

} }

namespace pepper { namespace json {

  struct object
  {
    public:
      object() = default;
      virtual ~object() = default;

    private:
      json::meta _meta;
    protected:
      json::meta &meta(void);
    public:
      virtual void add(field &value);

    public:
      void iter(std::function<void (field &)> fn) const;
  };

  template <typename T, typename... Components> struct extended;

  template <typename T> struct extended<T> : public T
  { 
    extended() = default;
    virtual ~extended() = default;
  };

  template <typename T, typename Component, typename... Components> 
    struct extended<T, Component, Components...> 
      : public extended<T, Components...>
      , public Component
  {
    extended() : Component{ this->meta() }
    {
      // DO NOTHING
    }
    virtual ~extended() = default;
  };

  template <typename... Components> 
    struct combined : public extended<object, Components...>
  {
    combined() = default;
    virtual ~combined() = default;
  };


} }

#endif
