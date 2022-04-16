#ifndef __PEPPER_JSON_TYPE_MAP_H__
#define __PEPPER_JSON_TYPE_MAP_H__

#include <pepper/json/type/value.hpp>
#include <pepper/json/cursor/named/accessor.hpp>

#include <map>

namespace pepper { namespace json { namespace type { namespace map {

  template <typename T>
    class value : public type::value, public std::map<std::string, T>
  {
    public:
      value() = default;
      virtual ~value() = default;

    public:
      T &at(const std::string &k)
      {
        return std::map<std::string, T>::operator[](k);
      }

      virtual void load_from(const cursor::object &curr)
      {
        const auto &value = curr.get_reader();

        this->clear();

        for (auto &member : value.getMemberNames())
        {
          cursor::object next{
            pepper::mem::shared::make<cursor::accessor, cursor::named::accessor>(curr, member)
          };

          (*this)[member].load_from( next );
        }
      }

      virtual void dump_into(cursor::object &curr) const
      {
        for (auto it = this->begin(); it != this->end(); ++it)
        {
          cursor::object next{
            pepper::mem::shared::make<cursor::accessor, cursor::named::accessor>(curr, it->first)
          };

          it->second.dump_into( next );
        }
      }
  };

} } } }

#endif
