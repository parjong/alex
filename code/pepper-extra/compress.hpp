#ifndef __PEPPER_COMPRESS_H__
#define __PEPPER_COMPRESS_H__

#include "pepper/pathname.hpp"

namespace pepper { namespace compress {

  struct backend
  {
    backend() = default;
    virtual ~backend() = default;

    virtual void add_recursively(const pepper::pathname::dir &r) const = 0;
  };

  class archive
  {
    private:
      std::unique_ptr<backend> _backend;

    public:
      archive(const pepper::pathname::file &out);
      ~archive() = default;

    public:
      void add_recursively(const pepper::pathname::dir &r) const;
  };

} }

#endif
