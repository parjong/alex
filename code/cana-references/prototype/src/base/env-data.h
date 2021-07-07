#ifndef BC_ENV_DATA_H__
#define BC_ENV_DATA_H__

#include <map>
#include <string>

class env_data
{
  public:
    env_data();
    env_data(char * const *envp);
  private:
    std::map<std::string, std::string> map_;
  public:
    void insert(const std::string& k, const std::string& v);
    void erase(const std::string& k);    
  public:
    char **data(void) const;
};

#endif
