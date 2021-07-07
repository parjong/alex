#ifndef GCC_OPTIONS_H__
#define GCC_OPTIONS_H__

#include "build/gcc_option.h"

#include <vector>

class GNUOptions
{
  public:
    GNUOptions();
    ~GNUOptions();
  private:
    std::vector<GNUOption *> options_;
  public:
    void append(GNUOption *arg);
    void accept(GNUOptionVisitor& v) const;
};

#endif
