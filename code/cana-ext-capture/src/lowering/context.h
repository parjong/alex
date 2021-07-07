#ifndef __CAPTURE_LOWERING_CONTEXT_H__
#define __CAPTURE_LOWERING_CONTEXT_H__

#include "observer.h"

#include <string>
#include <list>

namespace lowering {

  class context
  {
    private:
      std::list<std::string> &_arg;
      std::list<std::string> &_out;

    private:
      observer &_o;

    public:
      context(std::list<std::string> &arg, std::list<std::string> &out, observer &o);

    public:
      bool has_next(void) const;

      const std::string &front(void) const;
      void pop(void);

    public:
      void forward(const std::string &tok);
  };

}

#endif
