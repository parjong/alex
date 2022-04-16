#ifndef BC_ARG_DATA_H__
#define BC_ARG_DATA_H__

#include <string>
#include <vector>

class arg_tail : public std::vector<std::string>
{
  public:
    arg_tail();
};

class arg_data
{
  public:
    arg_data();
    arg_data(char * const *argv);       
  private:
    std::vector<std::string> opts_;
  public:
    void push_back(const std::string& opt);
  public:
    char **data(void) const;
  public:
    arg_tail tl(void) const;
};

#endif
