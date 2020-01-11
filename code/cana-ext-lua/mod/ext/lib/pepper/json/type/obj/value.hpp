#ifndef __PEPPER_JSON_TYPE_OBJ_VALUE_H__
#define __PEPPER_JSON_TYPE_OBJ_VALUE_H__

#include <pepper/json/type/meta.hpp>
#include <pepper/json/type/value.hpp>

namespace pepper { namespace json { namespace type { namespace obj {

  class value : public type::value
  {
    public:
      value() = default;
      virtual ~value() = default;

    private:
      meta _meta;
    public:
      void add_field(const std::string &name, type::value &field);

    public:
      virtual void load_from(const cursor::object &curr);
      virtual void dump_into(cursor::object &curr) const;
  };

} } } }

#endif
