#ifndef __PEPPER_ATTR_VALUE_READER_H__
#define __PEPPER_ATTR_VALUE_READER_H__

namespace pepper { namespace attr { namespace value {

  template <typename T> class reader
  {
    private:
      const T _value;

    public:
      reader(const T &value) : _value{ value }
      {
        // DO NOTHING
      }

    public:
      const T &operator()(void) const
      {
        return _value;
      }
  };

} } }

#endif
