#ifndef __PEPPER_JSON_ARCHIVE_DICT_H__
#define __PEPPER_JSON_ARCHIVE_DICT_H__

#include "pepper/json/archive/base.hpp"
#include "pepper/json/value/dict.hpp"

#include <json/json.h>

#include <map>
#include <string>

namespace pepper { namespace json {

  template <typename T> struct archive<dict<T>>
  {
    static void load(const Json::Value &json, dict<T> &obj)
    {    
      for (const auto &k : json.getMemberNames())
      {
        T v;
        archive<T>::load(json[k], v);
        obj[k] = v;
      }         
    }

    static void dump(Json::Value &json, const dict<T> &obj)    
    {
      for (auto it = obj.begin(); it != obj.end(); ++it)
      {
        Json::Value node(Json::objectValue);

        archive<T>::dump(node, it->second);

        json[it->first] = node;
      }
    }

    static void desc(Json::Value &json)    
    {      
      Json::Value node(Json::objectValue);
      archive<T>::desc(node);
      json["name"] = node;      
    }

  };

} }

#endif
