#include "env.hpp"

#include <cana/logging/point.hpp>

namespace cana { namespace rt { namespace preload {

  env::env(char **envp)
  {
    static cana::logging::point log{"cana.rt.preload.env.ctor"};

    for (char **cur = envp; *cur; ++cur)
    {
      char *mid = *cur;

      while (*mid != '=')
      {
        ++mid;
      }

      char *beg = *cur;

      std::string k{beg, static_cast<size_t>(mid - beg)};
      std::string v{mid + 1};

      log.debug("adding key '", k, "' and value '", v, "' (extracted from '", *cur, "')");

      _content[k] = v;
    }
  }

  bool env::lookup(const std::string &k, const std::function<void (const std::string &v)> &cb) const
  {
    auto it = _content.find(k);

    if (it == _content.end())
    {
      return false;
    }

    cb(it->second);
    return true;
  }

  void env::each(const std::function<void (const std::string &k, const std::string &v)> &cb) const
  {
    for (auto it = _content.begin(); it != _content.end(); ++it)
    {
      cb(it->first, it->second);
    }
  }

} } }
