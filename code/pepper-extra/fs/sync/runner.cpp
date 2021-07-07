#include "pepper/fs/sync/runner.hpp"
#include "pepper/fs/sync/log.hpp"

#include "pepper/except.hpp"

namespace pepper { namespace fs { namespace sync {

  pepper::logging::logger runner::_log{ sync::log, "runner" };

  runner::runner(sync::op::base &op)
    : _op( op )
  {
    //
  }

  void runner::sync(const boost::filesystem::path &from, const boost::filesystem::path &into)
  {
    static pepper::logging::logger log{ _log, __func__ };    

    namespace fs = boost::filesystem;

    log.info("sync %s with %s", from, into);

    if ( !fs::exists(from) )
    {
      log.debug("cannot find %s", from);

      return;
    }
    
    _log.debug( "%s exists", from);

    if ( !fs::is_directory(from) && !fs::exists(into) )
    {
      _log.debug( "%s is a file and %s does not exist", from, into );

      _op.on_file(from, into);
      return;
    }
     
    _log.debug( "%s is a directory, or %s does exist", from, into );
    
    if ( fs::exists(into) )
    {    
      if ( !fs::is_directory(from) && !fs::is_directory(into) )      
      {
        _log.debug( "detect file conflict between %s and %s", from, into );

        if ( !_op.on_file_conflict(from, into) )       
          return;      
      }
      else if ( fs::is_directory(from) && fs::is_directory(into) )
      {
        _log.debug( "detect directory conflict between %s and %s", from, into );

        if ( !_op.on_directory_conflict(from, into) )       
          return;      
      } 
      else
      {
        _log.debug( "detect incomaptible conflict between %s and %s", from, into );

        if ( !_op.on_incompatible_conflict(from, into) )       
          return;      
      }
    }
    else
    {
      _log.debug( "%s is a directory, and %s does not exist", from, into );
     
      if ( !_op.on_directory(from, into) )      
        return;      
    }

    _log.debug( "iterate over children" );

    for( fs::directory_iterator it(from) ; it != fs::directory_iterator() ; ++it )
    {
      fs::path fcurr{ it->path() };
      fs::path icurr{ into / fcurr.filename() };

      log.debug( "visit %s", fcurr.filename() );

      sync( fcurr, icurr );
    }

    return;
  }

} } }
