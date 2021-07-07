#ifndef __CAPTURE_LOWERING_OBSERVER_H__
#define __CAPTURE_LOWERING_OBSERVER_H__

#include <string>

namespace lowering {

  struct observer
  {
    virtual ~observer() = default;

    virtual void forward(const std::string &arg, const std::string &tok) = 0;
  };

}

#endif
