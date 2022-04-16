#include "plugin/init.h"

#include "plugin/manager.h"

#include "plugin/checker/basename.h"
#include "plugin/actor/gcc.h"

void setup(void) 
{ 
  static basename_checker gcc_chk("gcc-4.8");;
  static gcc_actor gcc_act;

  manager::instance().enroll(gcc_chk, gcc_act);
}
