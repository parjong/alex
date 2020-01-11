#ifndef __BUILD_H__
#define __BUILD_H__

#include "libdal/database.h"

#include <string>
#include <vector>

namespace build { 
  class store {
    private:
      database::conn &conn_;

    public:
      store(database::conn &conn);
      ~store();
     
    public:
      void  init_tables(void);

      int   create_session(void); 

      void  set_session_init_time(int session_id);
      void  set_session_fini_time(int session_id);

      int   get_last_session_id(void);

      int   create_command(int session_id);

      std::string get_command_cwd(int command_id);
      void  set_command_cwd(int command_id, const std::string &dir);
      
      std::string get_command_exe(int command_id);
      void  set_command_exe(int command_id, const std::string &dir);
      
      void  set_command_pid(int command_id, pid_t pid);
      void  set_command_ppid(int command_id, pid_t ppid);

      void  set_command_init_time(int command_id);
      void  set_command_fini_time(int command_id);

      void  get_command_arg(int command_id, std::vector<std::string> &out);
      void  set_command_arg(int command_id, int argc, char **argv);

      void  set_command_env(int command_id, char **envp);

      void  set_command_flow(int command_id, const std::string &src, const std::string &dst);

      void  set_command_pp_opt(int command_id, const std::vector<std::string>& opts);
      void  set_command_pp_out(int command_id, const std::string &out);
      void  set_command_pp_err(int command_id, const std::string &err);

    // DEBUGGING
    private:
      void log(int level, const std::string &msg);
    public:
      void fatal(const std::string &msg);
      void error(const std::string &msg);
      void warn(const std::string &msg);
      void info(const std::string &msg);
      void debug(const std::string &msg);
      void trivial(const std::string &msg);
  };
}

#endif
