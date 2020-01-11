#ifndef __PEPPER_JSON_SEQ_H__
#define __PEPPER_JSON_SEQ_H__

#include <pepper/json/type/value.hpp>
#include <pepper/json/cursor/index.hpp>

#include <vector>

namespace pepper { namespace json { namespace type { namespace seq {

  template <typename T> 
    class value : public type::value, public std::vector<T>
  {
    public:
      value() = default;
      virtual ~value() = default;

    public:
      virtual void load_from(const cursor::base &curr) 
      {        
        this->clear();

        int num = 0;

        for (auto &child : curr.get_reader())
        {
          cursor::index next{ curr, num++ };

          this->emplace(this->end())->load_from(next);
        }
      }

      virtual void dump_into(cursor::base &curr) const
      {      
        int ind = 0;

        for (auto it = this->begin(); it != this->end(); ++it)
        {
          cursor::index next{ curr, ind++ };

          it->dump_into( next );
        }
      }
  };

} } } }

#endif
