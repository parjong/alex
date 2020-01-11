#ifndef BC_DISTRIB_DATA_H__
#define BC_DISTRIB_DATA_H__

#include <string>

class distrib_data
{
  public:
    distrib_data(const std::string& base);
  public:
    std::string base_;
    std::string bin_;
    std::string lib_;
  public:
    const std::string &basedir(void) const;
    const std::string &bindir(void) const;
    const std::string &libdir(void) const;
  public:
    static distrib_data *build(void);
};

#endif
