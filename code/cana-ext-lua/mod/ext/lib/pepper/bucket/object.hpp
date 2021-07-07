#ifndef __PEPPER_BUCKET_OBJECT_H__
#define __PEPPER_BUCKET_OBJECT_H__

#include <pepper/maybe.hpp>
#include <pepper/vector.hpp>

#include <map>

namespace pepper { namespace bucket {

  template <typename K, typename V> class object 
  {
    private:
      std::map<K, pepper::vector::object<V>> _map;

    public:
      std::size_t size(void) const
      {
        return _map.size();
      }

    public:
      object<K, V> &insert(const K &k, const V &v)
      {
        auto it = _map.find(k);

        if ( it == _map.end() )
        {
          _map[k] = pepper::vector::object<V>{};
        }

        _map[k].emplace(v);

        return *this;
      }

    public:
      pepper::collection::object<V> &lookup(const K &key)
      {
        auto it = _map.find(key);

        if ( it == _map.end() )
        {
          static pepper::collection::builtin::empty::object<V> empty;
          return empty;
        }

        return (*it).second;
      }

    public:
      const object<K, V> &foreach(const std::function <void (const K &, const pepper::collection::object<V> &)> &fn) const
      {
        for (auto it = _map.begin(); it != _map.end(); ++it)
        {
          fn(it->first, it->second);
        }

        return *this;
      }

    public:
      object() = default;

    public:
      object(const object &) = delete;

    public:
      ~object() = default;
  };

} }

#endif
