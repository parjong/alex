#ifndef __CAPTURE_DATABASE_H__
#define __CAPTURE_DATABASE_H__

#include <string>

#include <sqlite3.h>

namespace database {
  class stmt {
    private:
      sqlite3_stmt *pStmt_;
    public:
      stmt(sqlite3_stmt *pStmt);
      ~stmt();

    public:
      stmt &reset(void);
      stmt &bind(int ind, int value);
      stmt &bind(int ind, const std::string &str);

      int step(void);

      int column_int(int ind);
      std::string column_string(int ind);

      int exec(void);      
  };  
}

namespace database {
  class conn {
    private:
      sqlite3 *db_;

    public:
      conn(sqlite3 *db);
      ~conn();

    public:
      stmt prepare(const std::string &query);

    public:
      static conn *open(const char *filename);
  };

  conn &operator<<(conn &lhs, const std::string &rhs);
  conn &operator<<(conn &lhs, stmt &s);
}

namespace database {
  class transaction {
    private:
      conn &conn_;
    public:
      transaction(conn &);
      ~transaction();
  };
}

#endif 
