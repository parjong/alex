#ifndef __PEPPER_OWNED_NESTED_MAP_H__
#define __PEPPER_OWNED_NESTED_MAP_H__

#include "pepper/owned/map.hpp"

namespace pepper { namespace owned {
  
  template <typename K1, typename K2, typename V> class nested_map
  {
    public:
      nested_map() = default;
      virtual ~nested_map() = default;

    private:
      map<K1, map<K2, V>> _content;

    public:
      bool is_member(const K1 &k1, const K2 &k2) const
      {
        if ( !_content.is_member(k1) )
          return false;
        return _content.lookup(k1).is_member(k2);
      }

    public:
      void iter(std::function<void (const K1 &k1, const K2 &k2, const V &v)> fn) const
      {
        auto outer_iter_fn = [&] (const K1 &k1, const map<K2, V> &m1)
        {
          auto inner_iter_fn = [&] (const K2 &k2, const V &v)
          {
            fn(k1, k2, v);
          };
          
          m1.iter(inner_iter_fn);
        };

        _content.iter(outer_iter_fn);
      }

    public:
      V &lookup(const K1 &k1, const K2 &k2)
      {
        return _content.lookup(k1).lookup(k2);
      }

      const V &lookup(const K1 &k1, const K2 &k2) const
      {
        return _content.lookup(k1).lookup(k2);
      }

    public:
      void insert(const K1 &k1, const K2 &k2, V *value)
      {
        if ( !_content.is_member(k1) )
        {
          _content.insert( k1, new map<K2, V>{ } );
        }

        _content.lookup(k1).insert(k2, value);
      }

      template <typename... Args>
        V &emplace(const K1 &k1, const K2 &k2, Args&... args)
      {
        if ( !_content.is_member(k1) )
        {
          _content.insert( k1, new map<K2, V>{ } );
        }

        return _content.lookup(k1).emplace(k2, args...);
      }


  };

} }
#endif
