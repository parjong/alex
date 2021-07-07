#ifndef __PEPPER_PATHNAME_GLOB_H__
#define __PEPPER_PATHNAME_GLOB_H__

#include <string>
#include <vector>

#include <boost/filesystem.hpp>

#include "pepper/logging/logger.hpp"

namespace pepper { namespace pathname {

  class glob 
  {
    private:
      static pepper::logging::logger _log;

    private:
      std::string _pattern;

    public:
      glob(const std::string &pattern);
      ~glob() = default;

    private:      
      typedef std::vector<std::string>::const_iterator iterator;          
      bool is_matched(const iterator pat_cur, const iterator pat_end, 
                      const iterator elm_cur, const iterator elm_end) const;
    public:
      bool is_matched(const boost::filesystem::path &path) const;
  };

} } 

#endif
