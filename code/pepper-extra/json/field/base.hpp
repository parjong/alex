#ifndef __PEPPER_JSON_BASE_FIELD_H__
#define __PEPPER_JSON_BASE_FIELD_H__

#include "pepper/opt.hpp"
#include "pepper/property.hpp"
#include "pepper/json/value/object.forward.hpp"

#include <json/json.h>

#include <string>

namespace pepper { namespace json {
 
  struct field 
  {
    struct meta
    {
      pepper::opt<std::string> desc;

      meta() = default;
      ~meta() = default;
    };

    field::meta _meta;

    field(object &o, const std::string &name);
    field(json::meta &meta, const std::string &name);

    virtual ~field() = default;        

    pepper::property::rw<std::string> name;

    virtual void load(const Json::Value &json) = 0;
    virtual void dump(Json::Value &json) const = 0;
    virtual void desc(Json::Value &json) const = 0;
  };

} }

#endif
