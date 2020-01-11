#ifndef __PEPPER_JSON_STR_H__
#define __PEPPER_JSON_STR_H__

#include <pepper/json/type/value.hpp>

#include <string>

namespace pepper { namespace json { namespace type { namespace str {

  class value : public type::value
  {
    private:
      std::string _str;

    public:
      value();

    public:
      virtual ~value() = default;

    public:
      operator const std::string &() const;
      value &operator=(const std::string &value);

    public:
      virtual void load_from(const cursor::base &c);
      virtual void dump_into(cursor::base &c) const;
  };

} } } }

#endif
