#ifndef __CANA_CORELIB_LOG_TEXT_FACTORY_H__
#define __CANA_CORELIB_LOG_TEXT_FACTORY_H__

#include <cana/log/factory.hpp>
#include <memory>

#include "file.hpp"

namespace cana { namespace corelib { namespace log { namespace text {

  class factory : public cana::log::factory
  {
    private:
      std::shared_ptr<text::file> _file;
      cana::log::level            _level;

    public:
      factory(const std::shared_ptr<text::file> &file, const cana::log::level &level);
      virtual ~factory() = default;

    public:
      virtual std::unique_ptr<cana::log::stream> make(const std::string &name) const;
  };

} } } }

#endif
