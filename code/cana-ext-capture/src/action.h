#ifndef __CAPTURE_ACTION_H__
#define __CAPTURE_ACTION_H__

#include <cana/proc/info.hpp>

#include <iostream>
#include <string>
#include <list>
#include <map>

#include <unistd.h>
#include <string.h>

#include "lowering/engine.h"
#include "parsing/engine.h"
#include "running/engine.h"

class action
{
  private:
    std::ostream &_os;
    std::string _path;

  public:
    lowering::engine  le;
    parsing::engine   pe;
    running::code     rcode;

  public:
    action(std::ostream &os, const std::string &path);

  private:
    void lower(lowering::context &ctx) const;
    bool parse(parsing::context &ctx) const;

  public:
    bool act(const cana::proc::info &pi) const;
};

#endif
