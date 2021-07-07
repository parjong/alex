#ifndef __PEPPER_JSON_CURSOR_INDEXED_ACCESSOR_H__
#define __PEPPER_JSON_CURSOR_INDEXED_ACCESSOR_H__

#include <pepper/json/cursor/accessor.hpp>
#include <pepper/json/cursor/object.hpp>

namespace pepper { namespace json { namespace cursor { namespace indexed {

  class accessor : public cursor::accessor
  {
    private:
      const cursor::object _cur;
      int _ind;

    public:
      accessor(const cursor::object &cur, int ind);

    public:
      virtual ~accessor() = default;

    public:
      virtual Json::Value &get_writer(void) const;
      virtual const Json::Value &get_reader(void) const;
  };

} } } }

#endif
