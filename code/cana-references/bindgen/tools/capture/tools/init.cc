#include <assert.h>

#include "libbuild/build.h"
#include "libdal/database.h"

int main(int argc, char **argv) {
  assert( argv[1] != nullptr );

  database::conn *pDB = database::conn::open(argv[1]);

  build::store s(*pDB);

  s.init_tables();

  int sid = s.create_session();
  s.set_session_init_time(sid);

  delete pDB;
}
