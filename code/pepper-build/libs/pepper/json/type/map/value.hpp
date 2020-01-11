#ifndef __PEPPER_JSON_MAP_H__
#define __PEPPER_JSON_MAP_H__

#include <pepper/json/type/value.hpp>
#include <pepper/json/cursor/field.hpp>

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

      virtual void load_from(const cursor::base &curr)
      {
        const auto &value = curr.get_reader();

        this->clear();

        for (auto &member : value.getMemberNames())
        {
          cursor::field next{ curr, member };
          (*this)[member].load_from( next );
        }
      }

      virtual void dump_into(cursor::base &curr) const
      {
        for (auto it = this->begin(); it != this->end(); ++it)
        {
          cursor::field next{ curr, it->first };          
          it->second.dump_into( next ); 
        }
      }
  };

} } } }

#endif
