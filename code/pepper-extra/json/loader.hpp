#ifndef __PEPPER_JSON_LOADER_H__
#define __PEPPER_JSON_LOADER_H__

#include "pepper/dict.hpp"
#include "pepper/json.hpp"
#include "pepper/pathname.hpp"

namespace pepper { namespace json {

  class loader
  {
    public:
      loader(const pepper::dict::base &dict);
      ~loader() = default;

    private:
      const pepper::dict::base &_dict;

    public:
      bool load(const pepper::pathname::file &file, Json::Value &into) const;
  };

}  } 

#endif
