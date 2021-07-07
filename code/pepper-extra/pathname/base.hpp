#ifndef __PEPPER_PATHNAME_BASE_H__
#define __PEPPER_PATHNAME_BASE_H__

#include <boost/filesystem.hpp>

#include <ostream>

namespace pepper
{
  namespace pathname
  {
    class base
    {
      private:
        boost::filesystem::path _path;

      public:
        base(const boost::filesystem::path &path);
        virtual ~base() = default;

      public:
        const boost::filesystem::path &path(void) const;
        const std::string basename(void) const;

      public:
        // TODO Add 'virtual'?
        bool does_exist(void) const;
    };   

    std::ostream &operator<<(std::ostream &os, const base &pn);
  }
}

#endif
