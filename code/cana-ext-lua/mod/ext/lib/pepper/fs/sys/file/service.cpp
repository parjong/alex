#include <pepper/fs/sys/file/service.hpp>
#include <pepper/fs/sys/file/make/session.hpp>
#include <pepper/fs/sys/file/open/session.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace fs { namespace sys { namespace file {

  pepper::fs::core::file::make::region service::make(const std::string &path) const
  {
    return pepper::fs::core::file::make::region{
      pepper::mem::shared::make<pepper::fs::core::file::make::session, pepper::fs::sys::file::make::session>( path )
    };
  }

  pepper::fs::core::file::open::region service::open(const std::string &path) const
  {
    return pepper::mem::shared::make<pepper::fs::core::file::open::session, pepper::fs::sys::file::open::session>( path );
  }
 
} } } }
