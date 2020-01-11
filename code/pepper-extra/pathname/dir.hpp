#ifndef __PEPPER_PATHNAME_DIR_H__
#define __PEPPER_PATHNAME_DIR_H__

#include "pepper/logging/logger.hpp"

#include "pepper/pathname/base.hpp"
#include "pepper/pathname/file.hpp"
#include "pepper/pathname/visitor/base.hpp"

namespace pepper { namespace pathname {

  class dir : public base
  {
    private:
      static pepper::logging::logger log;

    public:
      dir(const boost::filesystem::path &path);
      virtual ~dir() = default;

    public:
      static dir current(void);

    public:
      // mkdir -p
      bool create_all(void) const;
      // rm -rf
      bool remove_all(void) const;

    private:
      boost::filesystem::path child_path(const std::string &name) const;

    public:
      // chdir [path]
      void chdir(void) const;

    public:
      file child_file(const std::string &name) const;
      // TODO child_dir(const std::string &name)

    public:
      bool sync_recursively(const dir &into) const;

    public:
      void accept(visitor::base &v) const;
  };
  
} }

#endif
