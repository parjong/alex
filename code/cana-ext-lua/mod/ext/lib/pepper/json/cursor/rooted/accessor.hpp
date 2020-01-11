#ifndef __PEPPER_JSON_CURSOR_ROOTED_ACCESSOR_H__
#define __PEPPER_JSON_CURSOR_ROOTED_ACCESSOR_H__

#include <pepper/json/cursor/accessor.hpp>

namespace pepper { namespace json { namespace cursor { namespace rooted {

  class accessor : public cursor::accessor
  {
    private:
      Json::Value &_root;

    public:
      accessor(Json::Value &r);

    public:
      virtual ~accessor() = default;

    public:
      virtual Json::Value &get_writer(void) const;
      virtual const Json::Value &get_reader(void) const;
  };

} } } }

#endif
