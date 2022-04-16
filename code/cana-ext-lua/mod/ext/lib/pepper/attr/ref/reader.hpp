#ifndef __PEPPER_ATTR_REF_READER_H__
#define __PEPPER_ATTR_REF_READER_H__

namespace pepper { namespace attr { namespace ref {

  template <typename T> class reader
  {
    private:
      const T &_ref;

    public:
      reader(const T &ref) : _ref(ref)
      {
        // DO NOTHING
      }

    public:
      const T &operator()(void) const
      {
        return _ref;
      }
  };

} } }

#endif
