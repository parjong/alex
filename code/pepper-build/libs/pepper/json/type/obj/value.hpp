#ifndef __PEPPER_JSON_VALUE_OBJECT_H__
#define __PEPPER_JSON_VALUE_OBJECT_H__

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
      virtual void load_from(const cursor::base &curr);
      virtual void dump_into(cursor::base &curr) const;
  };

} } } }

#endif
