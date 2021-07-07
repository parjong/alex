#include "pepper/cli/option/base.hpp"

#include "pepper/cli/app/base.hpp"

namespace pepper { namespace cli { namespace option {
  
  base::base(app::base &cmd, const std::string &head, const std::string &desc)
    : _head{ head }
    , _desc{ desc }
  {
    cmd.add_option( *this );
  }

  const std::string &base::head(void) const 
  {
    return _head;
  }

  void base::show_desc(std::ostream &os) const
  {
    os << _desc;
  }

} } }
