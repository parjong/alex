#ifndef __PEPPER_DICT_OBJECT_H__
#define __PEPPER_DICT_OBJECT_H__

#include <pepper/dict/maybe/reader.hpp>

#include <map>

namespace pepper { namespace dict {

  template <typename K, typename V> class object 
  {
    private:
      std::map<K, V> _map;

    public:
      object() = default;
      ~object() = default;

    public:
      std::map<K, V> &raw(void)
      {
        return _map;
      }

      const std::map<K, V> &raw(void) const
      {
        return _map;
      }

    public:
      object<K, V> &insert(const K &key, const V &val)
      {
        _map[key] = val;
        return *this;
      }

    public:
      pepper::maybe::object<V> lookup(const K &key) const
      {
        auto it = _map.find(key);

        if (it == _map.end())
        {
          return pepper::maybe::none<V>();
        }

        return pepper::maybe::make<V, dict::maybe::reader<K, V>>()(it);
      }

    public:
      void foreach(const std::function<void (const K &, const V &)> &fn) const
      {
        for (auto it = _map.begin(); it != _map.end(); ++it) {
          fn(it->first, it->second);
        }
      }
  };

} }

#endif
