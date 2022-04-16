#ifndef __PEPPER_FS_RECURSIVE_SYNC_OP_H__
#define __PEPPER_FS_RECURSIVE_SYNC_OP_H__

#include "pepper/fs/sync/op/base.hpp"
#include "pepper/logging/logger.hpp"

namespace pepper { namespace fs { namespace sync { namespace op {

  struct recursive_sync : public base
  {
    private:
      static pepper::logging::logger _log;

    public:
      recursive_sync() = default;
      virtual ~recursive_sync() = default;

    public:
      virtual void on_file(const path &from, const path &into);
      virtual bool on_directory(const path &from, const path &into);      
      virtual bool on_file_conflict(const path &from, const path &into);
      virtual bool on_directory_conflict(const path &from, const path &into);
      virtual bool on_incompatible_conflict(const path &from, const path &into);
  };

} } } }

#endif
