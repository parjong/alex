#include "manager.hpp"
#include "point.hpp"

namespace
{
  struct stream : public cana::log::stream
  {
    stream()          = default;
    virtual ~stream() = default;

    virtual cana::log::level level(void) const
    {
      return cana::log::LOG_NONE;
    }

    virtual void fatal(const std::string &) { return; }
    virtual void error(const std::string &) { return; }
    virtual void warn(const std::string &)  { return; }
    virtual void info(const std::string &)  { return; }
    virtual void debug(const std::string &) { return; }
    virtual void trace(const std::string &) { return; }
  };

  struct factory : public cana::log::factory
  {
    factory() = default;
    virtual ~factory() = default;

    virtual std::unique_ptr<cana::log::stream> make(const std::string &name) const
    {
      return std::unique_ptr<cana::log::stream>{new stream()};
    }
  };

  cana::logging::manager *object;
}

namespace cana { namespace logging {

  manager::manager() : _fac{new ::factory()}
  {
    // DO NOTHING
  }

  void manager::attach(logging::point *p)
  {
    _points.insert(p);
  }

  void manager::detach(logging::point *p)
  {
    _points.erase(p);
  }

  void manager::reload(void)
  {
    for (auto point : _points)
    {
      point->reset();
    }
  }

  const log::factory &manager::get(void) const
  {
    return *_fac;
  }

  manager &manager::set(const cana::log::backend &b)
  {
    _fac = std::move(b.make());
    reload();
  }

  manager &manager::instance(void)
  {
    if (::object == nullptr)
    {
      ::object = new manager{};
    }

    return *::object;
  }

} }
