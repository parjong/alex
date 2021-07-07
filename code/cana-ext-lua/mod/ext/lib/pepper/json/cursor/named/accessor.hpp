#ifndef __PEPPER_JSON_CURSOR_NAMED_ACCESSOR_H__
#define __PEPPER_JSON_CURSOR_NAMED_ACCESSOR_H__

#include <pepper/json/cursor/accessor.hpp>
#include <pepper/json/cursor/object.hpp>

namespace pepper { namespace json { namespace cursor { namespace named {

  class accessor : public cursor::accessor
  {
    private:
      cursor::object _cur;
      std::string _tag;

    public:
      accessor(const cursor::object &cur, const std::string &tag);

    public:
      virtual ~accessor() = default;

    public:
      virtual Json::Value &get_writer(void) const;
      virtual const Json::Value &get_reader(void) const;
  };

} } } }

#endif
