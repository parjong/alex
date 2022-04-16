#include "database.h"

#include <string.h>
#include <stdexcept>

namespace database {
  stmt::stmt(sqlite3_stmt *pStmt) : pStmt_(pStmt) { 
    // DO NOTHING
  }

  stmt::~stmt() { 
    sqlite3_finalize(pStmt_);
  }    

  stmt &stmt::reset(void) {
    sqlite3_reset(pStmt_);
    return *this;
  }

  stmt &stmt::bind(int ind, int value) {
    sqlite3_bind_int(pStmt_, ind, value);
    return *this;
  }

  stmt &stmt::bind(int ind, const std::string &str) {
    sqlite3_bind_text(pStmt_, ind, str.c_str(), str.size(), SQLITE_STATIC);
    return *this;
  }


  int stmt::step(void) {
    return sqlite3_step(pStmt_);
  }

  int stmt::column_int(int ind) {
    return sqlite3_column_int(pStmt_, ind);
  }

  std::string stmt::column_string(int ind) {
    return reinterpret_cast<const char *>(sqlite3_column_text(pStmt_, ind));
  }

  int stmt::exec(void) {
    reset();
    return step();
  }
}

namespace database {
  conn::conn(sqlite3 *db) : db_(db) { }

  conn::~conn() {
    sqlite3_close(db_);
  }

  stmt conn::prepare(const std::string &query) {
    sqlite3_stmt *pStmt = nullptr;

    int rc = sqlite3_prepare(db_, query.c_str(), query.size(), &pStmt, nullptr);

    if ( rc == SQLITE_OK ) {
      return stmt(pStmt);
    }

    throw std::runtime_error(sqlite3_errmsg(db_));
  }

  conn *conn::open(const char *filename) {
    sqlite3 *db = nullptr;

    int rc = sqlite3_open(filename, &db);

    if ( !rc ) {
      return new conn(db);
    }

    sqlite3_close(db);
    return nullptr;
  }

  conn &operator<<(conn& lhs, const std::string &rhs) {
    lhs.prepare(rhs).exec();
    return lhs;
  }

  conn &operator<<(conn &lhs, stmt &s) {
    s.step();
    return lhs;
  }
}

namespace database {
  transaction::transaction(conn &conn) : conn_(conn) { 
    conn_ << "BEGIN TRANSACTION"; 
  }
  
  transaction::~transaction() {
    conn_ << "END TRANSACTION";
  }
}


