#ifndef __PEPPER_JSON_META_H__
#define __PEPPER_JSON_META_H__

#include <pepper/json/type/value.hpp>

#include <map>
#include <string>

namespace pepper { namespace json { namespace type {

  class meta 
  {
    public:
      meta() = default;
      ~meta() = default;

    private:
      std::map<std::string, type::value *> _fields;
    public:
      void add(const std::string &name, type::value &field);

    public:
      void load_from(const cursor::base &curr);
      void dump_into(cursor::base &curr) const;
  };

} } }

#endif
