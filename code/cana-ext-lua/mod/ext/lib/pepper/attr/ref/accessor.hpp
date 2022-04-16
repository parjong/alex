#ifndef __PEPPER_ATTR_REF_ACCESSOR_H__
#define __PEPPER_ATTR_REF_ACCESSOR_H__

namespace pepper { namespace attr { namespace ref {

  template <typename T> class accessor
  {
    private:
      T &_value;

    public:
      T &operator()(void)
      {
        return _value;
      }

    public:
      const T &operator()(void) const
      {
        return _value;
      }

    public:
      accessor<T> &operator=(const T &value)
      {
        _value = value;
        return *this;
      }

    public:
      accessor(T &value) : _value( value )
      {
        // DO NOTHING
      }

    public:
      ~accessor() = default;
  };

} } }

#endif
