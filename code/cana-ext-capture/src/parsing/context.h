#ifndef __CAPTURE_PARSING_CONTEXT_H__
#define __CAPTURE_PARSING_CONTEXT_H__

#include "observer.h"

#include <memory>
#include <list>
#include <map>

namespace parsing {

  struct context
  {
    std::list<std::string> &_args;
    std::map<std::string, std::list<std::string>> &_tags;

    observer &_observer;

    bool _error;

    context(std::list<std::string> &args,
            std::map<std::string, std::list<std::string>> &tags,
            parsing::observer &observer);

    bool has_next() const;

    void stop(void);
    void tagged(const std::string &arg, const std::string &tag);
  };

}

#endif
