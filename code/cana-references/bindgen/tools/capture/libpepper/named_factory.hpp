#ifndef __NAMED_FACTORY_H__
#define __NAMED_FACTORY_H__

#include "named.hpp"
#include "factory.hpp"

namespace pepper {
  template <typename T> struct named_factory : public named<factory<T>> {
    named_factory() = default;
    virtual ~named_factory() = default;
  };
}

#endif
