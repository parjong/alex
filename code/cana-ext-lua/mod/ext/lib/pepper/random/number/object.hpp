#ifndef __PEPPER_RANDOM_NUMBER_OBJECT_H__
#define __PEPPER_RANDOM_NUMBER_OBJECT_H__

#include <pepper/stream.hpp>

namespace pepper { namespace random { namespace number {

  class object : public pepper::stream::object<int>
  {
    public:
      object() = default;
      virtual ~object() = default;

    public:
      virtual pepper::stream::data::bean<int> stream(void) const;
  };

} } }

#endif
