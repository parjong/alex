#ifndef __PEPPER_JSON_TYPE_NUM_VALUE_H__
#define __PEPPER_JSON_TYPE_NUM_VALUE_H__

#include <pepper/json/type/value.hpp>

namespace pepper { namespace json { namespace type { namespace num {

  class value : public type::value
  {
    private:
      int _num;

    public:
      value();
      value(int n);

    public:
      virtual ~value() = default;

    public:
      operator int() const;
      value &operator=(int n);

    public:
      virtual void load_from(const cursor::object &);
      virtual void dump_into(cursor::object &c) const;
  };

} } } }

#endif
