#include "base/arg-data.h"
#include "base/env-data.h"
#include "base/debug-tools.h"
#include "base/owned.hpp"

#include "monitor/lib/filename-tools.h"
#include "monitor/lib/exec-tools.h"

#include "monitor/ptrace/ptrace-child.h"
#include "monitor/ptrace/ptrace-observer.h"
#include "monitor/ptrace/ptrace-monitor.h"

#include <boost/format.hpp>

#include <assert.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/time.h>

#include <sqlite3.h>

#include <iostream>

static debug::logger file_logger = debug::logger::instance().get_child(__FILE__);

class command
{
  friend class database;
  private:
    command(sqlite3 *db, sqlite3_int64 row) : db_(db), row_(row) { }
  private:
    sqlite3 *db_;
    sqlite3_int64 row_;
  private:
    long timestamp(void) const
    {
      struct timeval tv;

      gettimeofday(&tv, NULL);

      return tv.tv_sec * 1000 + tv.tv_usec / 1000;
    }
  public:
    void start(void)
    {
      sqlite3_stmt *stmt = NULL;

      sqlite3_prepare(db_, "UPDATE CMD SET bTimestamp = ? WHERE ID = ?", -1, &stmt, NULL);
      
      sqlite3_reset(stmt);
      sqlite3_bind_int64(stmt, 1, timestamp());
      sqlite3_bind_int(stmt, 2, row_);
      sqlite3_step(stmt);

      sqlite3_finalize(stmt);
    }
  public:
    void end(void)
    {
      sqlite3_stmt *stmt = NULL;

      sqlite3_prepare(db_, "UPDATE CMD SET eTimestamp = ? WHERE ID = ?", -1, &stmt, NULL);

      sqlite3_reset(stmt);
      sqlite3_bind_int64(stmt, 1, timestamp());
      sqlite3_bind_int(stmt, 2, row_);
      sqlite3_step(stmt);

      sqlite3_finalize(stmt);
    }
};

class database
{
  public:
    database();  
    ~database();   
  private:
    sqlite3 *db_;
  public:
    command *insert(const std::string& exe, const std::vector<std::string>& arg, const std::vector<std::string>& env);
  public:
    int open(const std::string& filename);        
  public:
    void close(void);
  private:
    void exec(const std::string& query);
  public:
    void initialize(void);    
};

database::database() : db_(nullptr) {  }
database::~database() 
{
  sqlite3_close(db_);
}

int database::open(const std::string& filename)
{ 
  return sqlite3_open(filename.data(), &db_);
}    

void database::close(void) { sqlite3_close(db_); }

void database::exec(const std::string& query)
{
  static debug::logger func_logger = file_logger.get_child(__FUNCTION__);

  int rc = sqlite3_exec(db_, query.data(), nullptr, nullptr, nullptr);

  LOG_DEBUG( func_logger, "rc = " << rc );
}

void database::initialize(void)
{     
  exec( "PRAGMA synchronous = OFF;" );

  exec( "BEGIN TRANSACTION" );
  
  exec( "CREATE TABLE CMD(ID INTEGER PRIMARY KEY AUTOINCREMENT, PATH TEXT NOT NULL, bTimestamp INTEGER, eTimestamp INTEGER);" );      

  exec( "CREATE TABLE ARG_MAP(ID INTEGER PRIMARY KEY AUTOINCREMENT, CMD_ID INTEGER NOT NULL, NTH INTEGER NOT NULL, TOK_ID INTEGER NOT NULL);" );      
  exec( "CREATE TABLE ARG_TOK(ID INTEGER PRIMARY KEY AUTOINCREMENT, VALUE TEXT UNIQUE ON CONFLICT IGNORE);" );      

  exec( "CREATE TABLE ENV_MAP(ID INTEGER PRIMARY KEY AUTOINCREMENT, CMD_ID INTEGER NOT NULL, NTH INTEGER NOT NULL, TOK_ID INTEGER NOT NULL);" );      
  exec( "CREATE TABLE ENV_TOK(ID INTEGER PRIMARY KEY AUTOINCREMENT, VALUE TEXT UNIQUE ON CONFLICT IGNORE);" );      

  exec( "END TRANSACTION" );
}

command *database::insert(const std::string& exe, const std::vector<std::string>& arg, const std::vector<std::string>& env)
{
  sqlite3_exec(db_, "BEGIN TRANSACTION", 0, 0, 0);

  sqlite3_stmt *cmd_stmt = NULL;

  sqlite3_prepare(db_, "INSERT INTO CMD (PATH) VALUES (?)", -1, &cmd_stmt, NULL);

  sqlite3_reset(cmd_stmt);
  sqlite3_bind_text(cmd_stmt, 1, exe.data(), -1, NULL);
  sqlite3_step(cmd_stmt);

  sqlite3_int64 cmd_row = sqlite3_last_insert_rowid(db_);

  /** ... */
  sqlite3_stmt *arg_tok_stmt = NULL;
  sqlite3_stmt *arg_map_stmt = NULL;

  sqlite3_stmt *env_tok_stmt = NULL;
  sqlite3_stmt *env_map_stmt = NULL;

  sqlite3_prepare(db_, "INSERT INTO ARG_TOK (VALUE) VALUES (?)", -1, &arg_tok_stmt, NULL);
  sqlite3_prepare(db_, "INSERT INTO ARG_MAP (CMD_ID, NTH, TOK_ID) SELECT ?, ?, ARG_TOK.ID FROM ARG_TOK WHERE ARG_TOK.VALUE = ?", -1, &arg_map_stmt, NULL);

  sqlite3_prepare(db_, "INSERT INTO ENV_TOK (VALUE) VALUES (?)", -1, &env_tok_stmt, NULL);
  sqlite3_prepare(db_, "INSERT INTO ENV_MAP (CMD_ID, NTH, TOK_ID) SELECT ?, ?, ENV_TOK.ID FROM ENV_TOK WHERE ENV_TOK.VALUE = ?", -1, &env_map_stmt, NULL);

  for (size_t i = 0; i < arg.size(); ++i)
  {
    sqlite3_reset(arg_tok_stmt);
    sqlite3_bind_text(arg_tok_stmt, 1, arg[i].data(), -1, NULL);
    sqlite3_step(arg_tok_stmt);

    sqlite3_reset(arg_map_stmt);
    sqlite3_bind_int(arg_map_stmt, 1, cmd_row);
    sqlite3_bind_int(arg_map_stmt, 2, i);
    sqlite3_bind_text(arg_map_stmt, 3, arg[i].data(), -1, NULL);
    sqlite3_step(arg_map_stmt);
  }

  for (size_t i = 0; i < env.size(); ++i)
  {
    sqlite3_reset(env_tok_stmt);
    sqlite3_bind_text(env_tok_stmt, 1, env[i].data(), -1, NULL);
    sqlite3_step(env_tok_stmt);

    sqlite3_reset(env_map_stmt);
    sqlite3_bind_int(env_map_stmt, 1, cmd_row);
    sqlite3_bind_int(env_map_stmt, 2, i);
    sqlite3_bind_text(env_map_stmt, 3, env[i].data(), -1, NULL);
    sqlite3_step(env_map_stmt);
  }

  sqlite3_finalize(env_map_stmt);
  sqlite3_finalize(env_tok_stmt);

  sqlite3_finalize(arg_map_stmt);
  sqlite3_finalize(arg_tok_stmt);

  sqlite3_exec(db_, "COMMIT TRANSACTION", 0, 0, 0);

  return new command(db_, cmd_row);
}

class status
{
  public:
    status(const std::string& exe, const std::vector<std::string>& arg, const std::vector<std::string>& env)
      : exe_(exe), arg_(arg), env_(env)
    { }
  private:
    std::string exe_;
    std::vector<std::string> arg_; 
    std::vector<std::string> env_;
  public:
    const std::string& exe(void) const { return exe_; }
    const std::vector<std::string>& arg(void) const { return arg_; }
    const std::vector<std::string>& env(void) const { return env_; }
};

class basic_observer : public observer
{
  public:
    basic_observer(database& db) : db_(db) { }
    virtual ~basic_observer() { }
  private:
    database& db_;
  private:
    std::map<pid_t, status *>   staged_;
    std::map<pid_t, command *>  committed_;
  private:
    void on_terminated(pid_t pid)
    {
      static debug::logger func_logger = file_logger.get_child(__FUNCTION__);

      auto it = committed_.find(pid);
    
      if ( it == committed_.end() )
      {
        LOG_DEBUG( func_logger, "** PID " << pid << " suddenly terminated" );

        return;
      }
      
      /** Log the end time */
      command *cmd = it->second;

      cmd->end();

      committed_.erase(pid);
      delete cmd;
    }

  public:
    virtual void on_exited(pid_t child) { on_terminated(child); }
    virtual void on_signaled(pid_t child) { on_terminated(child); }

    virtual void on_fork(pid_t child) { return; }
    virtual void on_clone(pid_t child) { return; }
    virtual void on_vfork(pid_t child) { return; }
    virtual void on_vfork_done(pid_t child) { return; }
    virtual void on_exit(pid_t child) { return; }
    virtual void on_exec(pid_t pid)       
    { 
      auto it = staged_.find(pid);

      if ( it == staged_.end() ) return;
 
      status *proc = it->second;

      /** Append to the database */
      command *cmd = 
        db_.insert(proc->exe(), proc->arg(), proc->env());
      
      committed_[pid] = cmd;

      /** Log the start time */
      cmd->start();

      /** Remove from 'staged_' */
      staged_.erase(pid);
      delete proc;      
    }       

    virtual void on_enter(pid_t pid, struct user_regs_struct& regs) 
    {
      static debug::logger func_logger = file_logger.get_child(__FUNCTION__);

      LOG_DEBUG( func_logger, "** PID " << pid << " enters syscall(" << regs.orig_rax << ")");

      LOG_DEBUG( func_logger, "** reg.orig_rax: " << regs.orig_rax );
      LOG_DEBUG( func_logger, "** reg.rax: " << regs.rax );
      LOG_DEBUG( func_logger, "** reg.rdi: " << regs.rdi );
      LOG_DEBUG( func_logger, "** reg.rsi: " << regs.rsi );
      LOG_DEBUG( func_logger, "** reg.rdx: " << regs.rdx );

      if ( regs.orig_rax != 59 ) return;
      
      child tracee(pid);

      auto it = staged_.find(pid);

      if ( it != staged_.end() )
      {
        delete it->second;
      }

      staged_[pid] = new status( tracee.read( (const char *) regs.rdi ),
                                  tracee.read( (const char * const *) regs.rsi ),
                                  tracee.read( (const char * const *) regs.rdx ) );
    }

    virtual void on_leave(pid_t child, struct user_regs_struct& regs) 
    {
      static debug::logger func_logger = file_logger.get_child(__FUNCTION__);

      LOG_DEBUG( func_logger, "** PID " << child << " leaves syscall(" << regs.orig_rax << ")");
      LOG_DEBUG( func_logger, "** regs.orig_rax: " << regs.orig_rax );
      LOG_DEBUG( func_logger, "** regs.rax: " << regs.rax );
      LOG_DEBUG( func_logger, "** regs.rdi: " << regs.rdi );
      LOG_DEBUG( func_logger, "** regs.rsi: " << regs.rsi );
      LOG_DEBUG( func_logger, "** regs.rdx: " << regs.rdx );
    }

    virtual void fork(pid_t child) { return; }
};

void do_child(const std::string& path, const arg_data& arg, const env_data& env)
{
  static debug::logger func_logger = file_logger.get_child(__FUNCTION__);

  LOG_DEBUG(func_logger, "do_child(" << path << ")");

  if ( ptrace(PTRACE_TRACEME, 0, NULL, NULL) < 0 )
  {
    LOG_ERROR(func_logger, "ptrace(PTRACE_TRACEME, 0, NULL, NULL) failed: " << strerror(errno));
  }

  run_in_current(path, arg, env);
}

void do_parent(database& db, pid_t child)
{
  monitor m;

  basic_observer o(db);

  m.add(o);
  m.trace(child);

  /** Wait untile the child terminates */
  waitpid(child, NULL, 0);
}

/**
 * wrapper <argv 0> <argv 1> ... <argv n>
 */
int main(int argc, char * const *argv, char * const *envp)
{
  static debug::logger func_logger = file_logger.get_child(__FUNCTION__);

  /** Initialize debugging tools */
  debug::manager::init();
 
  assert( argv[1] && "argv[1] should be the output file" );
  assert( argv[2] && "argv[2] should be the command" );

  std::string path( owned<char>( filename_tools::resolve(argv[2]), free ) );
    
  LOG_INFO( func_logger, "resolve('" << argv[2] << "') = " << path );

  arg_data arg( argv + 2 );
  env_data env( envp );

  pid_t child = fork();

  if ( child == -1 )
  {
    LOG_ERROR( func_logger, "fork() failed: " << strerror(errno) );
    exit(1);
  }

  if ( child == 0 )
  {
    do_child(path, arg, env);    
  }
  else
  {
    database db;

    db.open( argv[1] );
    db.initialize();

    do_parent(db, child);

    db.close();
  }

  return 0;
}
