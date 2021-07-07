#include "env-data.h"

#include <assert.h>
#include <string.h>

env_data::env_data() { }
env_data::env_data(char * const *envp)
{
  for (char * const *cur = envp; *cur; ++cur)
  {
    std::string entry = *cur;

    size_t off = entry.find_first_of('=');

    assert( off != std::string::npos && "invalid entry" );

    std::string k = entry.substr(0, off);
    std::string v = entry.substr(off + 1, std::string::npos);

    map_[k] = v;
  }
}

void env_data::insert(const std::string& k, const std::string& v)
{
  map_[k] = v;
}

void env_data::erase(const std::string& k)
{
  map_.erase(k);
}


char **env_data::data(void) const 
{
  char **ret = (char **) calloc(map_.size() + 1, sizeof(char *));

  char **cur = ret;

  for (auto it = map_.begin(); it != map_.end(); ++it)
  {
    std::string str = it->first + "=" + it->second;

    *(cur++) = strdup( str.data() );
  }

  *cur = NULL;

  return ret;
}
