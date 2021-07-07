#include "build.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <memory>
#include <exception>

#include <boost/regex.hpp>


namespace build {
  store::store(database::conn &conn) : conn_(conn) 
  {
    // DO NOTHING
  }
 
  store::~store() { }
  
  void store::init_tables(void) {
    // Insert Speed Up
    conn_ << "PRAGMA synchronous = OFF";
    conn_ << "PRAGMA journal_mode = MEMORY";

    // Create a table
    conn_ << "CREATE TABLE IF NOT EXISTS session(id INTEGER PRIMARY KEY AUTOINCREMENT, initTime TIMESTAMP, finiTime TIMESTAMP);";
    conn_ << "CREATE TABLE IF NOT EXISTS command(id INTEGER PRIMARY KEY AUTOINCREMENT, session_id INTEGER, ppid INTEGER, pid INTEGER, wd TEXT, exe TEXT, initTime TIMESTAMP, finiTime TIMESTAMP, FOREIGN KEY(session_id) REFERENCES session(id))";    
    conn_ << "CREATE TABLE IF NOT EXISTS arg(id INTEGER PRIMARY KEY AUTOINCREMENT, command_id INTEGER, token TEXT, FOREIGN KEY(command_id) REFERENCES command(id))";
    conn_ << "CREATE TABLE IF NOT EXISTS env(id INTEGER PRIMARY KEY AUTOINCREMENT, command_id INTEGER, key TEXT, value TEXT, FOREIGN KEY(command_id) REFERENCES command(id))";
    
    conn_ << "CREATE TABLE IF NOT EXISTS flow(id INTEGER PRIMARY KEY AUTOINCREMENT, command_id INTEGER, src TEXT, dst TEXT, FOREIGN KEY(command_id) REFERENCES command(id))";

    conn_ << "CREATE TABLE IF NOT EXISTS pp_opt(id INTEGER PRIMARY KEY AUTOINCREMENT, command_id INTEGER, token TEXT, FOREIGN KEY(command_id) REFERENCES command(id))";
    conn_ << "CREATE TABLE IF NOT EXISTS pp_out(id INTEGER PRIMARY KEY AUTOINCREMENT, command_id INTEGER, content TEXT, FOREIGN KEY(command_id) REFERENCES command(id))";
    conn_ << "CREATE TABLE IF NOT EXISTS pp_err(id INTEGER PRIMARY KEY AUTOINCREMENT, command_id INTEGER, content TEXT, FOREIGN KEY(command_id) REFERENCES command(id))";

    // For debugging
    conn_ << "CREATE TABLE IF NOT EXISTS log(id INTEGER PRIMARY KEY AUTOINCREMENT, time TIMESTAMP, lv INTEGER, msg TEXT)";

  }

  /**
   *
   */
  int store::create_session(void) {
    database::transaction t(conn_);
    
    conn_ << "INSERT INTO session DEFAULT VALUES";

    database::stmt s = conn_.prepare("SELECT MAX(id) FROM session");
  
    while ( SQLITE_ROW == s.step() ) {
      return s.column_int(0);
    }

    return -1;
  }

  void store::set_session_init_time(int sid) {
    conn_ << conn_.prepare("UPDATE session SET initTime = CURRENT_TIMESTAMP WHERE id = ?").bind(1, sid);
  }

  void store::set_session_fini_time(int sid) {
    conn_ << conn_.prepare("UPDATE session SET finiTime = CURRENT_TIMESTAMP WHERE id = ?").bind(1, sid);
  }

  int store::get_last_session_id(void) {
    database::stmt s = conn_.prepare("SELECT MAX(id) FROM session");

    while ( SQLITE_ROW == s.step() ) {
      return s.column_int(0);
    }

    return -1;
  }

  /**
   *
   */
  int store::create_command(int session_id) {
    database::transaction t(conn_);

    conn_ << conn_.prepare("INSERT INTO command(session_id) VALUES (?)").bind(1, session_id);

    database::stmt s = conn_.prepare("SELECT MAX(id) FROM command");

    while ( SQLITE_ROW == s.step() ) {
      return s.column_int(0);
    }
    
    return -1;
  }

  std::string store::get_command_cwd(int command_id) {
    database::stmt s = conn_.prepare("SELECT wd FROM command WHERE id = ?");

    s.bind(1, command_id);

    while ( SQLITE_ROW == s.step() ) {
      return s.column_string(0);
    }
    
    throw std::runtime_error("Failed to find the string"); 
  }

  void store::set_command_cwd(int command_id, const std::string &dir) {
    conn_ << conn_.prepare("UPDATE command SET wd = ? WHERE id = ?").bind(1, dir).bind(2, command_id);
  }

  std::string store::get_command_exe(int command_id) {
    database::stmt s = conn_.prepare("SELECT exe FROM command WHERE id = ?");

    s.bind(1, command_id);

    while ( SQLITE_ROW == s.step() ) {
      return s.column_string(0);
    }
    
    throw std::runtime_error("Failed to find the command"); 
  }

  void store::set_command_exe(int command_id, const std::string &exe) {
    conn_ << conn_.prepare("UPDATE command SET exe = ? WHERE id = ?").bind(1, exe).bind(2, command_id);
  }

  void store::set_command_pid(int cid, pid_t pid) {
    conn_ << conn_.prepare("UPDATE command SET pid = ? WHERE id = ?").bind(1, pid).bind(2, cid);
  }

  void store::set_command_ppid(int cid, pid_t ppid) {
    conn_ << conn_.prepare("UPDATE command SET ppid = ? WHERE id = ?").bind(1, ppid).bind(2, cid);
  }

  void store::set_command_init_time(int cid) {
    conn_ << conn_.prepare("UPDATE command SET initTime = CURRENT_TIMESTAMP WHERE id = ?").bind(1, cid);
  }

  void store::set_command_fini_time(int cid) {
    conn_ << conn_.prepare("UPDATE command SET finiTime = CURRENT_TIMESTAMP WHERE id = ?").bind(1, cid);
  }

  void store::get_command_arg(int command_id, std::vector<std::string> &out) {
    database::stmt s = conn_.prepare("SELECT token FROM arg WHERE command_id = ? ORDER BY id ASC");

    s.bind(1, command_id);

    while ( SQLITE_ROW == s.step() ) {
      out.push_back( s.column_string(0) );
    }
  }

  void store::set_command_arg(int command_id, int argc, char **argv) {
    database::stmt s = conn_.prepare("INSERT INTO arg(command_id, token) VALUES (?, ?)");

    for (int i = 0; i < argc; ++i) {
      conn_ << s.reset().bind(1, command_id).bind(2, argv[i]);
    }
  }

  void store::set_command_env(int command_id, char **envp) {
    database::stmt s = conn_.prepare("INSERT INTO env(command_id, key, value) VALUES (?, ?, ?)");

    static boost::regex re("([^=]+)=(.*)");

    char **cur = envp;

    while ( *cur ) {
      boost::cmatch cm;
      boost::regex_match (*(cur++), cm, re);

      std::string k = cm[1];
      std::string v = cm[2];

      conn_ << s.reset().bind(1, command_id).bind(2, k).bind(3, v);
    }
  }

  void store::set_command_flow(int command_id, const std::string &src, const std::string &dst) {
    conn_.prepare("INSERT INTO flow(command_id, src, dst) VALUES (?, ?, ?)").bind(1, command_id).bind(2, src).bind(3, dst).step();
  }

  void store::set_command_pp_opt(int command_id, const std::vector<std::string> &opts) {
    database::stmt s = conn_.prepare("INSERT INTO pp_opt(command_id, token) VALUES (?, ?)");

    for (auto it = opts.begin(); it != opts.end(); ++it) {
      conn_ << s.reset().bind(1, command_id).bind(2, *it);
    }
  }


  void store::set_command_pp_out(int command_id, const std::string &content) {
    conn_.prepare("INSERT INTO pp_out(command_id, content) VALUES (?, ?)").bind(1, command_id).bind(2, content).step();
  }

  void store::set_command_pp_err(int command_id, const std::string &content) {
    conn_.prepare("INSERT INTO pp_err(command_id, content) VALUES (?, ?)").bind(1, command_id).bind(2, content).step();
  }

  /**
   *
   */
  void store::log(int level, const std::string &msg) {
    database::stmt s = conn_.prepare("INSERT INTO log(time, lv, msg) VALUES (CURRENT_TIMESTAMP, ?, ?)");    
    conn_ << s.bind(1, level).bind(2, msg);
  }

  void store::fatal(const std::string &msg) {
    log(0, msg);
  }

  void store::error(const std::string &msg) {
    log(1, msg);
  }

  void store::warn(const std::string &msg) {
    log(2, msg);
  }

  void store::info(const std::string &msg) {
    log(3, msg);
  }

  void store::debug(const std::string &msg) {
    log(4, msg);
  }

  void store::trivial(const std::string &msg) {
    log(5, msg);
  }

}
