#ifndef __PEPPER_OWNED_MAP_H__
#define __PEPPER_OWNED_MAP_H__

#include "pepper/except.hpp"

#include <map>
#include <memory>

namespace pepper { namespace owned {
  
  template <typename K, typename V> class map
  {
    public:
      map() = default;
      virtual ~map() = default;
      
    private:
      std::map<K, std::unique_ptr<V>> _map;
    public:
      size_t size(void) const 
      {
        return _map.size();
      }

      bool is_member(const K &k) const
      {
        return _map.find(k) != _map.end();
      }

      V &insert(const K &k, V *v)
      {
        _map[k] = std::unique_ptr<V>(v);

        return *v;
      }
      
      template <typename... Args> 
        V &emplace(const K &k, Args... args)
      {
        return this->insert(k, new V{ args... });
      }

      V &lookup(const K &k) 
      {
        auto it = _map.find(k);

        if ( it == _map.end() )
          pepper::throw_exn("cannot find '%s'", k);

        return *( it->second.get() );
      }

      const V &lookup(const K &k) const
      {
        auto it = _map.find(k);

        if ( it == _map.end() )
          pepper::throw_exn("cannot find '%s'", k);

        return *( it->second.get() );
      }
       
      bool eval(const K &k, std::function<void (const V &)> fn) const
      {
        auto it = _map.find(k);

        if ( it == _map.end() )
          return false;

        fn( *(it->second.get()) );
        return true;
      }

      void iter(std::function<void (const V &)> fn) const
      {
        for (const auto &elem : _map)
        {
          fn( *( elem.second.get() ) );
        }
      }

      void iter(std::function<void (const K &, const V &)> fn) const
      {
        for (const auto &elem : _map)
        {
          fn( elem.first, *( elem.second.get() ) );
        }
      }

  };

} }

#endif
