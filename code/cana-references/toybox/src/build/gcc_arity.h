#ifndef GCC_ARITY_H__
#define GCC_ARITY_H__

#include <map>
#include <string>

class GNUArity
{
  public:
    GNUArity();
  private:
    std::map<std::string, int> arities_;
  public:
    int lookup(const std::string& opt);
  public:
    static GNUArity& instance();
};

#endif
