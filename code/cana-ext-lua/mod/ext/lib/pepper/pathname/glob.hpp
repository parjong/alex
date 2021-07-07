#ifndef __PEPPER_PATHNAME_GLOB_H__
#define __PEPPER_PATHNAME_GLOB_H__

#include <string>
#include <vector>

#include <boost/filesystem.hpp>

namespace pepper { namespace pathname {

  class glob
  {
    private:
      std::vector<std::string> _tokens;

    public:
      glob(const std::string &pattern);
      ~glob() = default;

    public:
      bool match(const boost::filesystem::path &p) const;
  };

} }

#endif
