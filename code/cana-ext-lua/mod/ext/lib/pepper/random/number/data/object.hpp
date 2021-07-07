#ifndef __PEPPER_RANDOM_NUMBER_DATA_OBJECT_H__
#define __PEPPER_RANDOM_NUMBER_DATA_OBJECT_H__

#include <pepper/stream.hpp>

namespace pepper { namespace random { namespace number { namespace data {

  class object : public pepper::stream::data::object<int>
  {
    public:
      virtual pepper::stream::head::bean<int> head(void) const;

    public:
      object() = default;
      virtual ~object() = default;
  };

} } } }

#endif
