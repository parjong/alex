#ifndef __CAPTURE_PARSING_OBSERVER_H__
#define __CAPTURE_PARSING_OBSERVER_H__

#include <string>

namespace parsing {

  struct observer
  {
    virtual ~observer() = default;

    virtual void tagged(const std::string &arg, const std::string &tag) = 0;
  };

}

#endif
