#ifndef __PEPPER_DICT_MAYBE_READER_H__
#define __PEPPER_DICT_MAYBE_READER_H__

#include <pepper/maybe.hpp>

#include <map>

namespace pepper { namespace dict { namespace maybe {

  template <typename K, typename V> class reader : public pepper::maybe::reader<V>
  {
    public:
      typename std::map<K, V>::const_iterator _cur;

    public:
      reader(const typename std::map<K, V>::const_iterator &cur) : _cur{cur}
      {
        // DO NOTHING
      }

    public:
      virtual ~reader() = default;

    public:
      virtual bool filled(void) const
      {
        return true;
      }

      virtual bool read(const typename pepper::maybe::reader<V>::probe &p) const
      {
        p(_cur->second);
        return true;
      }
  };

} } }

#endif
