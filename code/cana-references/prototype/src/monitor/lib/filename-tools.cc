#include "monitor/lib/filename-tools.h"

#include "base/owned.hpp"

#include <boost/tokenizer.hpp>

#include <string.h>
#include <unistd.h>

std::string filename_tools::search_path(void)
{
  char *str = getenv("PATH");

  if ( str != nullptr )
  {
    return std::string(str);
  }

  size_t len = confstr(_CS_PATH, NULL, (size_t) 0);
  owned<char> buf((char *) malloc(len), free);
  confstr(_CS_PATH, buf, len);
  return std::string(buf);
}

char *filename_tools::resolve(const char *filename)
{
  if ( strchr(filename, '/') != nullptr )
  {
    return strdup(filename);
  }

  boost::char_separator<char> sep(":");
  boost::tokenizer< boost::char_separator<char> > tokens( filename_tools::search_path(), sep);

  for (const std::string& dir : tokens)
  {
    std::string candidate = dir + "/" + filename;

    if ( access( candidate.c_str(), X_OK ) == 0 )    
    {
      return strdup( candidate.c_str() );    
    }
  }

  return nullptr;
}

