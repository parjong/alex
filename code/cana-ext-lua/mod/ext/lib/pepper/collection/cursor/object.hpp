#ifndef __PEPPER_COLLECTION_CURSOR_OBJECT_H__
#define __PEPPER_COLLECTION_CURSOR_OBJECT_H__

#include <pepper/stream/head.hpp>
#include <pepper/collection/reader.hpp>

namespace pepper { namespace collection { namespace cursor {

  template <typename T> class object : public stream::head::object<T>, public collection::reader<T>
  {
    public:
      object() = default;
      virtual ~object() = default;

    public:
      virtual maybe::object<T> access(void) const final
      {
        return access(0);
      }

    public:
      virtual maybe::object<T> access(unsigned off) const = 0;

    public:
      virtual void forward(void) final
      {
        forward(1);
      }

    public:
      virtual void forward(unsigned off) = 0;
  };

} } }

#endif
