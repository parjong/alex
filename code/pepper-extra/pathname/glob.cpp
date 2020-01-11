#include "pepper/pathname/glob.hpp"

#include <deque>
#include <boost/algorithm/string.hpp>

#include <fnmatch.h>
#include "pepper/pathname/log.hpp"

namespace pepper { namespace pathname {

  pepper::logging::logger glob::_log{ pathname::log, "glob" };

  glob::glob(const std::string &pattern)
    : _pattern{ pattern }
  {
  }

  bool glob::is_matched(const iterator pat_cur, const iterator pat_end, 
                        const iterator elm_cur, const iterator elm_end) const
  {
    static pepper::logging::logger log{ _log, __func__ };

    if ( pat_cur >= pat_end && elm_cur >= elm_end )
    {
      log.debug( "return true if both pattern and path are empty" );
      return true;
    }

    if ( pat_cur >= pat_end || elm_cur >= elm_end )
    {
      log.debug( "return false if one of pattern or path is empty, but the other is not" );
      return false;
    }

    const auto &pat = *pat_cur;
    const auto &elm = *elm_cur;


    if ( pat == "**" )
    {
      for (auto elm_new = elm_cur; elm_new != elm_end; ++elm_new)
      {
        if ( is_matched(pat_cur + 1, pat_end, elm_new, elm_end) )
        {          
          return true;
        }
      }

      return false;
    }

    if ( fnmatch( pat.c_str(), elm.c_str(), FNM_PATHNAME ) != 0 ) {     
      log.debug( "return false when '%s' and '%s' are unmatched", pat.c_str(), elm.c_str() );
      return false;
    }

    log.debug( "compare the rest when '%s' and '%s' are matched", pat, elm );

    return is_matched(pat_cur + 1, pat_end, elm_cur + 1, elm_end);
  }

  bool glob::is_matched(const boost::filesystem::path &path) const
  {        
    static pepper::logging::logger log{ _log, __func__ };

    log.info( "match '%s' with '%s'", _pattern, path );
    std::vector<std::string> patterns;
    std::vector<std::string> elements;
    
    boost::algorithm::split(patterns, _pattern, boost::algorithm::is_any_of("/"));
    boost::algorithm::split(elements, path.string(), boost::algorithm::is_any_of("/"));


    return is_matched(patterns.begin(), patterns.end(), elements.begin(), elements.end());
  }


} }
