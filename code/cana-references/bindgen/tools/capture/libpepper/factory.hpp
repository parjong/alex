#ifndef __ACTION_FACTORY_H__
#define __ACTION_FACTORY_H__

namespace pepper {
  template <typename T> struct factory {
    factory() = default;
    virtual ~factory() = default;

    virtual T *create() = 0;
  };  
}

#endif
