#ifndef __PEPPER_APPFW_CLI_TRAIL_H__
#define __PEPPER_APPFW_CLI_TRAIL_H__

#include <pepper/appfw/cli/unit.hpp>
#include <pepper/collection.hpp>

namespace pepper { namespace appfw { namespace cli {

  class trail
  {
    private:
      std::vector<unit> _units;
   
    public:
      trail()   = default;
      ~trail()  = default;

    public:
      unit &push(const std::shared_ptr<pepper::appfw::app::desc> &app)
      {
        _units.emplace_back(app);

        return _units.back();
      }
  };
 
} } }

#endif
