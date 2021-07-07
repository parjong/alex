#include "base/arg-data.h"
#include "base/env-data.h"
#include "base/distrib-data.h"
#include "base/debug-tools.h"
#include "base/owned.hpp"
#include "monitor/lib/filename-tools.h"
#include "monitor/lib/exec-tools.h"
#include "monitor/lib/hook.h"

#include <assert.h>

#include <string.h>
#include <string>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include <iostream>

namespace fs = boost::filesystem;

static debug::logger file_logger = debug::logger::instance().get_child(__FILE__);

/**
 * wrapper <argv 0> <argv 1> ... <argv n>
 */
int main(int argc, char * const *argv, char * const *envp)
{
  static debug::logger func_logger = file_logger.get_child(__FUNCTION__);

  debug::manager::init();

  assert( argv[1] && "argv[1] should be present" );

  std::string path( owned<char>( filename_tools::resolve(argv[1]), free ) );
    
  LOG_INFO( func_logger, "execve(" << path << ")" );

  arg_data arg( argv + 1 );
  env_data env( envp );

  /** Construct 'distrib' */
  fs::path img_path     = fs::system_complete(argv[0]);
  fs::path distrib_path = img_path.parent_path().parent_path();

  distrib_data dist( distrib_path.string() );

  /** set BC_DISTRIB_DIR */
  env.insert("BC_DISTRIB_DIR", dist.basedir());

  /** enable LD_PRELOAD hook */
  hook::libc_plugin libc_hook(dist);

  libc_hook.enable(env);

  return run_in_current(path, arg, env);
}
