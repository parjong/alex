#include "pepper/fs/sync/op/recursive_sync.hpp"
#include "pepper/fs/sync/log.hpp"

#include "pepper/except.hpp"

namespace pepper { namespace fs { namespace sync { namespace op {

  pepper::logging::logger recursive_sync::_log{ sync::log, "recursive_sync" };

  void recursive_sync::on_file(const path &from, const path &into)
  {   
    _log.debug( "copy %s into %s", from, into );
    boost::filesystem::copy(from, into);
  }

  bool recursive_sync::on_directory(const path &from, const path &into)
  {    
    _log.debug( "create %s that corresponds to %s", into, from );
    boost::filesystem::create_directory( into );
    return true;
  }

  bool recursive_sync::on_file_conflict(const path &from, const path &into)
  {
    pepper::throw_exn("%s is overwritten by %s", into, from);
  }
  
  bool recursive_sync::on_directory_conflict(const path &from, const path &into)
  {
    _log.debug( "step into %s", into );
    return true;
  }

  bool recursive_sync::on_incompatible_conflict(const path &from, const path &into)
  {
    pepper::throw_exn("%s is incompatible with %s", from, into);
  }

} } } }
