#ifndef __PEPPER_ATTR_VALUE_ACCESSOR_H__
#define __PEPPER_ATTR_VALUE_ACCESSOR_H__

namespace pepper { namespace attr { namespace value {

  template <typename T> class accessor
  {
    private:
      T _value;

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
      accessor() : _value{ }
      {
        // DO NOTHING
      }

    public:
      accessor(const T &value) : _value{ value }
      {
        // DO NOTHING
      }

    public:
      ~accessor() = default;
  };

} } }

#endif
