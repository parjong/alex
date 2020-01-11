#ifndef __PEPPER_VIEW_CURSOR_H__
#define __PEPPER_VIEW_CURSOR_H__

#include <pepper/collection.hpp>

namespace pepper { namespace view {

  template <typename T> class cursor : public collection::cursor::object<T>
  {
    private:
      const collection::cursor::object<T> &_base;
      unsigned _curr;

    public:
      cursor(const collection::cursor::object<T> &base)
        : _base( base )
        , _curr{ 0 }
      {
        // DO NOTHING
      }
      virtual ~cursor() = default;

    public:
      virtual void forward(unsigned off)
      {
        _curr += off;
      }

      virtual maybe::object<T> access(unsigned off) const
      {
        return _base.access( _curr + off );
      }
  };

} }

#endif
