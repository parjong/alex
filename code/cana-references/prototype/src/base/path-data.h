#ifndef BC_PATH_DATA_H__
#define BC_PATH_DATA_H__

#include <unistd.h>

#include <string>

class path_data
{
  public:
    path_data(const char *path) 
    {
      char *abspath = realpath(path, NULL);

      provided_   = path;
      normalized_ = abspath;

      free(abspath);
    }
  private:
    std::string provided_;
    std::string normalized_;
  public:
    const std::string& provided(void) const { return provided_; }
    const std::string& normalized(void) const { return normalized_; }
};


#endif
