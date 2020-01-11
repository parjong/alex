#ifndef __PEPPER_FMT_VALUE_H__
#define __PEPPER_FMT_VALUE_H__

#include <pepper/fmt/base.hpp>

namespace pepper { namespace fmt {

  template <typename... Args> class value;

  template <> class value<> : public base
  {
    public:
      value() = default;
      virtual ~value() = default; 

    public:
      virtual std::ostream &output(std::ostream &os) const
      {
        return os;
      }
  };

  template <typename Arg, typename ... Args> 
    class value<Arg, Args...> : public base
  {
    private:
      const Arg &_head;
      value<Args...> _tail;

    public:
      value(const Arg &head, const Args&... tail) : _head(head), _tail{ tail... }
      {
        // DO NOTHING
      }

      virtual ~value() = default;

    public:
      virtual std::ostream &output(std::ostream &os) const
      {
        os << _head;
        os << _tail;
        return os;
      }
  };

} }

#endif
