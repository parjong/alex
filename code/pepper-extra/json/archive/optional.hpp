#ifndef __PEPPER_JSON_ARCHIVE_OPTIONAL_H__
#define __PEPPER_JSON_ARCHIVE_OPTIONAL_H__

#include "pepper/json/archive/base.hpp"

#include "pepper/opt.hpp"

namespace pepper { namespace json {

  template <typename T> struct archive<pepper::opt<T>>
  {
    static void load(const Json::Value &json, pepper::opt<T> &obj)
    {    
      T value;
      archive<T>::load(json, value);
      obj = value;
    }

    static void dump(Json::Value &json, const pepper::opt<T> &obj)    
    {
      archive<T>::dump(json, obj.get());
    }
  };

} }

#endif
