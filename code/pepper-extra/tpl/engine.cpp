#include "pepper/tpl/engine.hpp"

#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace pepper { namespace tpl { namespace action {

  void copy::perform(const pepper::subst &, const fs::path &from, const fs::path &into) const
  {
    fs::copy(from, into);         
  }
 
} } }

namespace pepper { namespace tpl { namespace action {

  void rewrite::perform(const pepper::subst &subst, const fs::path &from, const fs::path &into) const
  {
    boost::filesystem::fstream is( from, std::ios_base::in );
    boost::filesystem::fstream os( into, std::ios_base::out );

    for ( std::string line; std::getline( is, line ) ; )
    {
      os << subst.rewrite(line) << std::endl;
    }
  }

} } }

namespace pepper { namespace tpl { namespace action {

  void ignore::perform(const pepper::subst &, const fs::path &from, const fs::path &into) const
  {
    // DO NOTHING
  }
 
} } }


namespace pepper { namespace tpl {

  engine::engine(const pepper::dict::base &dict, const action::base &action)
    : _subst{ dict }, _action( action )
  {
    // DO NOTHING
  }

  void engine::add_action(const pepper::pathname::glob &glob, const action::base &action)
  {  
    _actions.emplace_back(&glob, &action);
  }

  const action::base &engine::find_action(const fs::path &path)
  {
    for (const auto &action : _actions)
    {
      if ( action.first->is_matched(path) )
        return *( action.second );
    }

    return _action;
  }
  
  bool engine::create(const fs::path &src, const fs::path &dst)
  {
    // TODO Use pepper::pathname::visitor
    
    // Check whether the function call is valid
    if( !fs::exists(src) || !fs::is_directory(src) )        
    {
      // TODO Throw an error
      return false;
    }

    if( !fs::exists(dst) )
    {
      // Create the destination directory if not exists
      fs::create_directory(dst);
    }

    // Iterate through the source directory
    for( fs::directory_iterator it(src); it != fs::directory_iterator(); ++it )
    {
      fs::path curr_path(it->path());

      std::string curr_name = curr_path.filename().string();
      std::string copy_name = _subst.rewrite(curr_name); 

      fs::path copy_path = dst / copy_name;

      if ( fs::is_directory(curr_path) )
      {
        // Found directory: Recursion
        if( !create( curr_path, copy_path ) )
        {
          return false;
        }
      }
      else 
      {
        find_action(curr_path).perform(_subst, curr_path, copy_path);
      }
    }

    return true;
  }


} }
