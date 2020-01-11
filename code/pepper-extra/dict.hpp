#ifndef __PEPPER_DICT_H__
#define __PEPPER_DICT_H__

#include <pepper/opt.hpp>

#include <map>
#include <string>

namespace pepper { namespace dict {

  struct base
  {
    base() = default;
    virtual ~base() = default;
  
    virtual void set(const std::string &k, const std::string &v) = 0;
    virtual pepper::opt<std::string> get(const std::string &k) const = 0;
  };

  class atomic : public base
  {
    public:
      atomic() = default;
      virtual ~atomic() = default;

    private:
      std::map<std::string, std::string> _map;

    public:
      void set(const std::string &k, const std::string &v)
      {
        _map[k] = v;
      }

      pepper::opt<std::string> get(const std::string &k) const
      {
        auto it = _map.find(k);

        if ( it == _map.end() )
        {
          return pepper::opt<std::string>{ };
        }

        return pepper::opt<std::string>{ it->second };
      }
  };

  class layered : public base
  {
    public:
      layered(const base &parent) : _parent(parent) 
      {
      }
      virtual ~layered() = default;


    private:
      const base &_parent;

    private:
      std::map<std::string, std::string> _map;

    public:
      void set(const std::string &k, const std::string &v)
      {
        _map[k] = v;
      }

      pepper::opt<std::string> get(const std::string &k) const
      {
        auto it = _map.find(k);

        if ( it == _map.end() )
        {
          return _parent.get(k);
        }

        return pepper::opt<std::string>{ it->second };
      }
  };

} }

#endif
