#include <pepper/pathname/glob.hpp>

#include <fnmatch.h>
#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>

#include <pepper/exn.hpp>

namespace {

  bool match(std::vector<std::string>::const_iterator cur_t,
             std::vector<std::string>::const_iterator end_t,
             boost::filesystem::path::const_iterator  cur_p,
             boost::filesystem::path::const_iterator  end_p) 
  {
    if ( cur_t == end_t && cur_p == end_p )
    {
      return true;
    }

    std::vector<std::string>::const_iterator new_t{ cur_t };
    boost::filesystem::path::const_iterator new_p{ cur_p };

    if ( *cur_t != "**" ) 
    {
      new_t++;
      new_p++;

      return ( fnmatch( cur_t->c_str(), cur_p->c_str(), FNM_PATHNAME ) == 0 )
        ? match( new_t, end_t, new_p, end_p)
        : false;
    }

    new_t++;

    for ( ; new_p != end_p; ++new_p )
    {
      if ( match(new_t, end_t, new_p, end_p) )
      {
        return true;
      }
    }

    return false;
  }
}
 
namespace pepper { namespace pathname {

  glob::glob(const std::string &pattern)
  {
    boost::char_separator<char> sep("/");
    boost::tokenizer<boost::char_separator<char>> tokens(pattern, sep);

    for (const auto &token : tokens)
    {
      _tokens.emplace_back(token);	
    }
  }

  bool glob::match(const boost::filesystem::path &p) const
  {
    return ::match( _tokens.begin(), _tokens.end(), 
                    p.begin(), p.end() );
  }

} }
