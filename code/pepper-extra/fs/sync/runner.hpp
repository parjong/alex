#ifndef __PEPPER_FS_SYNC_RUNNER_H__
#define __PEPPER_FS_SYNC_RUNNER_H__

#include "pepper/fs/sync/op/base.hpp"
#include "pepper/logging/logger.hpp"

#include <boost/filesystem.hpp>

namespace pepper { namespace fs { namespace sync {
  
  using path = boost::filesystem::path;

  class runner
  {
    private:
      static pepper::logging::logger _log;

    private:
      sync::op::base &_op;
    public:
      runner(sync::op::base &op);
      ~runner() = default;

    public:
      void sync(const path &from, const path &into);
  };

} } }

#endif
