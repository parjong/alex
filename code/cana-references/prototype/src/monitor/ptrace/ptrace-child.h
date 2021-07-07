#ifndef BC_PTRACE_CHILD_H__
#define BC_PTRACE_CHILD_H__

#include <sys/types.h>

#include <vector>
#include <string>

class child
{
  public:
    child(pid_t pid);
  private:
    pid_t pid_;
  public:
    std::string read(const char *addr);
    std::vector<std::string> read(const char * const *addr);
};


#endif
