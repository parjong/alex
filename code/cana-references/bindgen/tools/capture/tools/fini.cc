#include "libbuild/build.h"
#include "libdal/database.h"

int main(int argc, char **argv) {
  database::conn *pDB = database::conn::open(argv[1]);
  build::store s(*pDB);

  int sid = s.get_last_session_id();

  s.set_session_fini_time(sid);

  delete pDB;
}
