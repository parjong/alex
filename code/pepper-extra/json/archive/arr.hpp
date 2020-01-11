#ifndef __PEPPER_JSON_ARR_ARCHIVE_H__
#define __PEPPER_JSON_ARR_ARCHIVE_H__

#include "pepper/json/archive/base.hpp"
#include "pepper/json/value/arr.hpp"

#include <json/json.h>

#include <vector>


namespace pepper { namespace json {

  template <typename T> struct archive<arr<T>>
  {
    static void load(const Json::Value &json, arr<T> &obj)
    {    
      for (const auto &child : json)
      {
        T elem;
        archive<T>::load(child, elem);
        obj.push_back(elem);
      }         
    }

    static void dump(Json::Value &json, const arr<T> &obj)    
    {
      for (const auto &value : obj)
      {
        Json::Value elem;
        archive<T>::dump(elem, value);
        json.append(elem);
      }
    }

    static void desc(Json::Value &json)
    {
      Json::Value elem;
      archive<T>::desc(elem);
      json.append(elem);
    }

  };

} }

#endif
