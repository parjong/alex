#ifndef BC_BASENAME_CHECKER_H__
#define BC_BASENAME_CHECKER_H__

#include "plugin/checker.h"

class basename_checker : public checker
{
  public:
    basename_checker(const std::string& base);
  public:
    virtual ~basename_checker();
  private:
    std::string base_;
  public:
    virtual bool check(const std::string& path) const;
};

#endif
