#ifndef __CANA_LOGGING_MANAGER_H__
#define __CANA_LOGGING_MANAGER_H__

#include <cana/log/factory.hpp>
#include <cana/log/backend.hpp>

#include <set>

namespace cana { namespace logging {

  class point;

  class manager
  {
    private:
      std::unique_ptr<log::factory> _fac;
      std::set<logging::point *> _points;

    private:
      manager();

    public:
      ~manager() = default;

    public:
      void attach(logging::point *);
      void detach(logging::point *);

    public:
      void reload(void);

    public:
      const log::factory &get(void) const;
      manager &set(const cana::log::backend &backend);

    public:
      static manager &instance(void);
  };

} }

#endif
