#include "pepper/pathname/dir.hpp"
#include "pepper/pathname/log.hpp"

#include "pepper/fs.hpp"
#include "pepper/fs/sync.hpp"

#include <queue>
#include <iostream>

namespace pepper { namespace pathname {

  pepper::logging::logger dir::log{ pepper::pathname::log, "dir" };

  dir::dir(const boost::filesystem::path &path)
    : base{ path }
  {
    // DO NOTHING
  }

  bool dir::create_all(void) const 
  {
    static pepper::logging::logger log{ dir::log, __func__ };

    if ( does_exist() )
      return false;

    boost::filesystem::path full;

    for (auto &curr : path())
    {
      full /= curr;

      log.debug( "check %s", full );

      if ( !boost::filesystem::exists(full) )  
      {
        log.debug( "create %s", full );
        boost::filesystem::create_directory(full);   
      }
    }

    return true;
  }

  bool dir::remove_all(void) const
  {
    return boost::filesystem::remove_all(path());
  }

  void dir::chdir(void) const
  {
    boost::filesystem::current_path( path() );
  }

  boost::filesystem::path dir::child_path(const std::string &name) const
  {
    return path() / name;
  }

  file dir::child_file(const std::string &name) const
  {
    return file{ path() / name };
  }
  
  bool dir::sync_recursively(const dir &into) const
  {
    static pepper::logging::logger log{ dir::log, __func__ };   

    if ( !this->does_exist() )
    {
      log.warn( "%s does not exist", path() );
      return false;
    }

    log.info( "sync %s into %s", path(), into.path() );

    pepper::fs::sync::op::recursive_sync op;
    pepper::fs::sync::runner s{ op };

    s.sync( path(), into.path() );

    return true;
  }

  dir dir::current(void)
  {
    return dir{ boost::filesystem::current_path() };
  }

  void dir::accept(visitor::base &v) const
  {
    static pepper::logging::logger log{ dir::log, __func__ };   

    if ( !this->does_exist() )
    {
      log.warn( "%s does not exist", path() );
      return;
    }

    namespace fs = boost::filesystem;

    std::queue<fs::path> candidates;

    auto init_fn = [&] (const fs::path &elem)
    {
      candidates.push( elem.filename() );
    };

    // Starts from the direct children
    pepper::fs::iter_child(path(), init_fn);

    // Iterate over all the child
    while ( !candidates.empty() ) 
    {
      // Current candidate path
      const fs::path curr = candidates.front();
      const fs::path full = path() / curr;

      if ( fs::is_directory(full) )
      {        
        relative::dir dir_pn{ curr };
                        
        if ( v.visit( *this, dir_pn ) )
        {
          auto append_fn = [&] (const fs::path &elem)
          {
            candidates.push( curr / elem.filename() );
          };

          pepper::fs::iter_child(full, append_fn);
        }
      }
      else
      {
        relative::file file_pn{ curr };

        v.visit( *this, file_pn );
      }
 
      candidates.pop();
    }
  }

} }
