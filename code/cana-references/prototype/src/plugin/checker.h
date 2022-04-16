#ifndef BC_CHECKER_H__
#define BC_CHECKER_H__

#include <string>

class checker
{
  public:
    checker();
  public:
    virtual ~checker();
  public:
    virtual bool check(const std::string& path) const = 0;
};

#endif
