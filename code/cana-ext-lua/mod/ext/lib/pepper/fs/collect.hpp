#ifndef __PEPPER_FS_COLLECT_H__
#define __PEPPER_FS_COLLECT_H__

#include <boost/filesystem.hpp>

namespace pepper { namespace fs {

  struct visitor
  {
    visitor() = default;
    virtual ~visitor() = default;

    virtual void visit(const boost::filesystem::path &b, const boost::filesystem::path &r) = 0;
  };

} }

namespace pepper { namespace fs { 

  class collector
  {
    public:
      collector() = default;
      ~collector() = default;

    public:
      void collect(const boost::filesystem::path &base, visitor &v) const;
  };

} }


#endif
