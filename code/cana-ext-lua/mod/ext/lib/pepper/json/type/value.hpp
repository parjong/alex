#ifndef __PEPPER_JSON_TYPE_VALUE_H__
#define __PEPPER_JSON_TYPE_VALUE_H__

#include <pepper/json/cursor/object.hpp>

#include <iostream>

namespace pepper { namespace json { namespace type {

  class value
  {
    public:
      value() = default;
      virtual ~value() = default;

    public:
      virtual void load_from(const cursor::object &curr) = 0;
      virtual void dump_into(cursor::object &curr) const = 0;

    public:
      friend std::ostream &operator<<(std::ostream &os, const pepper::json::type::value &o);
      friend std::istream &operator>>(std::istream &is, pepper::json::type::value &o);
  };

} } }

#endif
