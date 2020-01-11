#ifndef __CANA_CORELIB_LOG_TEXT_BACKEND_H__
#define __CANA_CORELIB_LOG_TEXT_BACKEND_H__

#include <cana/core/storage.hpp>
#include <cana/log/backend.hpp>

#include "file.hpp"

#include <memory>

namespace cana { namespace corelib { namespace log { namespace text {

  class backend : public cana::log::backend
  {
    private:
      std::shared_ptr<text::file> _file;
      cana::log::level            _level;

    public:
      backend(const core::storage &);

    public:
      void set_level(const cana::log::level&);

    public:
      virtual ~backend() = default;

    public:
      virtual std::unique_ptr<cana::log::factory> make(void) const;
  };

} } } }

#endif
