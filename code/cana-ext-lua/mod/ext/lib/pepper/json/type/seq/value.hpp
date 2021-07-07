#ifndef __PEPPER_JSON_TYPE_SEQ_VALUE_H__
#define __PEPPER_JSON_TYPE_SEQ_VALUE_H__

#include <pepper/json/type/value.hpp>
#include <pepper/json/cursor/indexed/accessor.hpp>

#include <vector>

namespace pepper { namespace json { namespace type { namespace seq {

  template <typename T>
    class value : public type::value, public std::vector<T>
  {
    public:
      value() = default;
      virtual ~value() = default;

    public:
      virtual void load_from(const cursor::object &curr)
      {
        this->clear();

        int num = 0;

        for (auto &child : curr.get_reader())
        {
          cursor::object next{
            pepper::mem::shared::make<cursor::accessor, cursor::indexed::accessor>(curr, num++)
          };

          this->emplace(this->end())->load_from(next);
        }
      }

      virtual void dump_into(cursor::object &curr) const
      {
        int ind = 0;

        for (auto it = this->begin(); it != this->end(); ++it)
        {
          cursor::object next{
            pepper::mem::shared::make<cursor::accessor, cursor::indexed::accessor>(curr, ind++)
          };

          it->dump_into(next);
        }
      }
  };

} } } }

#endif
