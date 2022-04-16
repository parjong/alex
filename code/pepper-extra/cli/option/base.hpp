#ifndef __PEPPER_CLI_OPTION_BASE_H__
#define __PEPPER_CLI_OPTION_BASE_H__

#include "pepper/cli/app/base.forward.hpp"

#include "pepper/stream.hpp"

namespace pepper { namespace cli { namespace option {
  
  class base
  {
    private:
      const std::string _head;
      const std::string _desc;
    public:
      base(app::base &cmd, const std::string &head, const std::string &desc);
      virtual ~base() = default;

    public:
      const std::string &head(void) const;

    public:
      void show_desc(std::ostream &os) const;
      virtual void show_values(std::ostream &os) const = 0;

    public:     
      virtual void take(stream::base &ts) = 0;
    public:
      virtual void check(void) const = 0;
  };
  
} } }

#endif
