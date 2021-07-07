#include "monitor/ptrace/ptrace-child.h"

#include <sys/ptrace.h>

child::child(pid_t pid) : pid_(pid) { }

std::string child::read(const char *addr)
{
  std::string ret;

  const char *cur = addr;

  while (1)

  {
    long value = ptrace(PTRACE_PEEKDATA, pid_, cur, NULL);
    
    const char *ptr = (const char *) &value;
    
    size_t idx = 0;
    size_t len = sizeof(value);

    for (idx = 0; idx < len && ptr[idx] != '\0'; ++idx)
    {
      ret.push_back(ptr[idx]);
    }      

    if ( idx < len ) break;

    cur += len;
  }

  return ret;
}

std::vector<std::string> child::read(const char * const *addr)
{
  std::vector<std::string> ret;

  const char * const *cur = addr;

  while (1)
  {
    const char *ptr = (const char *) ptrace(PTRACE_PEEKDATA, pid_, cur, NULL);

    if ( ptr == NULL ) break;

    ret.push_back( read(ptr) );

    cur += 1;
  }
   
  return ret;

}
