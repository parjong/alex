#ifndef __PEPPER_FS_BASE_H__
#define __PEPPER_FS_BASE_H__

#include <boost/optional.hpp>
#include <boost/filesystem.hpp>

namespace pepper { namespace fs {

  using path = boost::filesystem::path;

  typedef std::function<bool (const path &)> path_pred;

  path discover_exn(const path &from, path_pred pred);
  boost::optional<path> discover_opt(const path &from, path_pred pred);

  typedef std::function<void (const path &)> path_func;

  // Apply 'fn' for each element in the given directory
  void iter_child(const path &p, path_func fn);

} }

#endif
