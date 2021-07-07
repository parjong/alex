#ifndef __PEPPER_JSON_HEADER_H__
#define __PEPPER_JSON_HEADER_H__

#include "pepper/json.hpp"

namespace pepper { namespace json { 

  namespace js = pepper::json;

  struct header : public js::object
  {
    header();
    virtual ~header() = default;

    js::opt<js::dict<std::string>> variables;
  };

} } 

#endif
