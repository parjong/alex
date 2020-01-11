#ifndef __PEPPER_FS_SYNC_BASE_OP_H__
#define __PEPPER_FS_SYNC_BASE_OP_H__

#include <boost/filesystem.hpp>

namespace pepper { namespace fs { namespace sync { namespace op {

  using path = boost::filesystem::path;

  struct base
  {
    base() = default;
    virtual ~base() = default;
   
    // 'from' is file, and 'into' does not exist
    virtual void on_file(const path &from, const path &into) = 0;
    // 'from' in directory, and 'into' does not exist
    //   step into if returns true
    virtual bool on_directory(const path &from, const path &into) = 0;
       
    // both 'from' and 'into' exist (and both are a file)
    virtual bool on_file_conflict(const path &from, const path &into) = 0;
    virtual bool on_directory_conflict(const path &from, const path &into) = 0;
    virtual bool on_incompatible_conflict(const path &from, const path &into) = 0;
  };

} } } }

#endif
