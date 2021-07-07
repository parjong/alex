#ifndef BC_FILENAME_TOOLS_H__
#define BC_FILENAME_TOOLS_H__

#include <string>

class filename_tools
{
  private:
    static std::string search_path(void);
  public: 
    static char *resolve(const char *filename);
};

#endif
