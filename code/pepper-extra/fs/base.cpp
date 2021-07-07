#include "pepper/fs/base.hpp"
#include "pepper/fs/log.hpp"

#include "pepper/except.hpp"

using namespace std::placeholders;

namespace pepper { namespace fs {
  
  // Assending
  boost::optional<path> discover_opt(const path &from, path_pred pred)
  {
    static pepper::logging::logger log{ fs::log, __func__ };

    log.info( "start from %s", from );

    boost::filesystem::path curr{ from };

    while ( !curr.empty() )
    {
      log.info( "visit %s", curr );

      if ( pred(curr) )
      {
        log.info( "return %s", curr );
        return curr;
      }

      curr = curr.parent_path();
    }

    return boost::none;
  }

  path discover_exn(const path &from, path_pred pred)
  {
    auto ret = discover_opt(from, pred);

    if ( ret ) 
      return ret.get();

    pepper::throw_exn( "cannot find the path that satisfies a given predicate" );
  }

  void iter_child(const path &p, path_func fn)
  {
    namespace fs = boost::filesystem;

    for ( fs::directory_iterator it{p}; it != fs::directory_iterator(); ++it )
    {
      const fs::path child{ it->path() };
      fn( child );
    }
  }
  
} }
