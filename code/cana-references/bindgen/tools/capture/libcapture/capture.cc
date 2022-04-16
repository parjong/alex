#include <boost/filesystem.hpp>

#include "libbuild/build.h"

#include "libcapture/toolchain.hpp"
#include "libcapture/backend.h"

namespace {
  int session_id = -1;
  int command_id = -1;

  database::conn *pConn = nullptr;
  build::store *pStore = nullptr;
}

void init(int argc, char **argv, char **envp) {
  // Allocate
  ::pConn = database::conn::open("build.db");
  ::pStore = new build::store(*::pConn);

  // Get the lastest session
  ::session_id = ::pStore->get_last_session_id();
 
  // Create a command
  ::command_id = ::pStore->create_command(session_id);
 
  // Fill the column in the command
  boost::filesystem::path cwd = boost::filesystem::current_path();
  boost::filesystem::path exe = boost::filesystem::read_symlink("/proc/self/exe");

  ::pStore->set_command_cwd(::command_id, cwd.string());
  ::pStore->set_command_exe(::command_id, exe.string());
  ::pStore->set_command_arg(::command_id, argc, argv); 
  // pStore->set_command_env(::command_id, envp);

  ::pStore->set_command_pid(::command_id, getpid());
  ::pStore->set_command_ppid(::command_id, getppid());

  // Set initTime
  ::pStore->set_command_init_time(::command_id); 
}

void fini(void) {
  // Set finiTime 
  ::pStore->set_command_fini_time(::command_id);

  // Full Path -> XML
  capture::compiler::context cc;
  capture::compiler::read_xml("compilers.xml", cc);
     
  // Get 'exe'
  auto exe = ::pStore->get_command_exe(::command_id);

  // Get 'xml'
  auto xml = cc.get(exe);

  // Run 'backend'
  if ( xml ) {
    capture::backend backend(*pStore, xml.get());
    backend.run(exe, ::command_id);
  }

  // Clean up
  delete pStore;
  delete pConn;
}

__attribute__((section(".init_array"))) void (*__init)(int, char **, char **) = init;
__attribute__((section(".fini_array"))) void (*__fini)(void) = fini;

