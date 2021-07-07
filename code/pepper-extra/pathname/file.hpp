#ifndef __PEPPER_PATHNAME_FILE_H__
#define __PEPPER_PATHNAME_FILE_H__

#include "pepper/pathname/base.hpp"

namespace pepper
{
  namespace pathname
  {
    class file : public base
    {
      public:
        file(const boost::filesystem::path &path);
        virtual ~file() = default;

      public:
        void create(void) const;
        void create(std::function<void (std::ostream &)> fn) const;
        void create(std::function<void (FILE *)> fn) const;

      public:
        void open(std::function<void (std::istream &)> fn) const;

      public:
        void remove(void) const;
    };
  }
}

#endif
