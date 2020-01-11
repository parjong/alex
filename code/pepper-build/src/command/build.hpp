#ifndef __PEPPER_BUILD_COMMAND_BUILD_H__
#define __PEPPER_BUILD_COMMAND_BUILD_H__

#include <cfg/ctxt.hpp>
#include <core/project/manifest/spec.hpp>

#include <pepper/appfw.hpp>

namespace command {

  class build : public pepper::appfw::apps::basic::desc
  {
    private:
      const cfg::ctxt &_ctxt;

    public:
      build(const cfg::ctxt &ctxt);
      virtual ~build() = default;

    public:
      virtual int main(pepper::appfw::apps::basic::service &args);
  };

}

#endif
