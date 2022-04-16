#ifndef __PEPPER_JSON_ARCHIVE_OTHER_H__
#define __PEPPER_JSON_ARCHIVE_OTHER_H__

#include "pepper/json/archive/base.hpp"
#include "pepper/json/field/base.hpp"

#include <type_traits>

namespace pepper { namespace json {

  template <typename T> struct archive
  {
    static void load(const Json::Value &json, T &obj)
    {
      auto load_fn = [&] (json::field &field)
      {
        field.load(json);
      };

      obj.iter(load_fn);
    }

    static void dump(Json::Value &json, const T &obj)    
    {
      auto dump_fn = [&] (json::field &field)
      {
        field.dump(json);
      };

      obj.iter(dump_fn);
    }

    static void desc(Json::Value &json)
    {
      T obj;

      auto desc_fn = [&] (json::field &fld)
      {
        fld.desc(json);
      };

      obj.iter(desc_fn);
    }
  };

} }

#endif
