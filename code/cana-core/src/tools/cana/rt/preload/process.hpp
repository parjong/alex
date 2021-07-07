#ifndef __CANA_RT_PRELOAD_PROCESS_H__
#define __CANA_RT_PRELOAD_PROCESS_H__

#include <cana/proc/info.hpp>

#include "record.hpp"

namespace cana { namespace rt { namespace preload {

  class process : public cana::proc::info
  {
    private:
      const preload::record &_record;

    public:
      process(const preload::record &);
      virtual ~process() = default;

    public:
      virtual const std::string &image(void) const;

    public:
      virtual const cana::proc::arg &arg(void) const;
      virtual const cana::proc::env &env(void) const;
  };

} } }

#endif
