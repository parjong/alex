#include <cana/rt/preload/record.hpp>
#include <cana/rt/preload/process.hpp>

#include <cana/logging/manager.hpp>
#include <cana/logging/point.hpp>

#include <cana/sys/object.hpp>

#include <cana/corelib/log/text/backend.hpp>
#include <cana/corelib/binding/json/binder.hpp>
#include <cana/corelib/loading/json/loader.hpp>

#include <fstream>
#include <cstdlib>

static cana::rt::preload::record  *record = nullptr;
static cana::rt::preload::process *process = nullptr;
static cana::sys::object *core = nullptr;

static cana::log::level get_level(int lv)
{
  if (lv == 0) return cana::log::LOG_NONE;
  if (lv == 1) return cana::log::LOG_FATAL;
  if (lv == 2) return cana::log::LOG_ERROR;
  if (lv == 3) return cana::log::LOG_WARN;
  if (lv == 4) return cana::log::LOG_INFO;
  if (lv == 5) return cana::log::LOG_DEBUG;
  if (lv == 6) return cana::log::LOG_TRACE;
  return cana::log::LOG_ALL;
}

int init(int argc, char **argv, char **envp)
{
  char *data = getenv("CANA_STORAGE");

  if (data == nullptr)
  {
    fprintf(stderr, "CANA_STORAGE is not specified\n");
    return 0;
  }

  cana::core::storage storage{data};

  cana::corelib::log::text::backend backend{storage};

  char *loglevel = getenv("CANA_LOGLEVEL");

  if (loglevel != nullptr)
  {
    backend.set_level(get_level(atoi(loglevel)));
  }

  cana::logging::manager::instance().set(backend);

  static cana::logging::point log{__FUNCTION__};

  log.info("create a record");
  record = new cana::rt::preload::record{
    boost::filesystem::canonical("/proc/self/exe"),
    argv,
    envp
  };

  log.info("create a process from image ", record->image());
  process = new cana::rt::preload::process{*record};

  log.info("create a system object");
  core = new cana::sys::object();

  log.info("load binders");
  char *coreconf = getenv("CANA_CORECONF");
  char *corehome = getenv("CANA_COREHOME");

  if (coreconf == nullptr)
  {
    log.warn("fail to read CANA_CORECONF");
  }
  else if (corehome == nullptr)
  {
    log.warn("fail to read CANA_COREHOME");
  }
  else
  {
    log.info("load a core configuration from '", coreconf, "'");

    std::ifstream ifs{coreconf};

    cana::corelib::binding::json::package   package{corehome};
    cana::corelib::binding::json::loader    loader{ifs, package};

    core->load(loader);
  }

  log.info("load apps");
  char *appconf = getenv("CANA_APPCONF");
  char *apphome = getenv("CANA_APPHOME");

  if (appconf == nullptr)
  {
    log.warn("fail to read CANA_APPCONF");
  }
  else if (apphome == nullptr)
  {
    log.warn("fail to read CANA_APPHOME");
  }
  else
  {
    log.info("load a app configuration from '", appconf, "'");
    std::ifstream ifs{appconf};

    cana::corelib::loading::json::package  package{apphome};
    cana::corelib::loading::json::loader   loader{ifs, package, storage};

    core->load(loader);
  }

  core->notifyProcessEnter(*process);
}

int fini(void)
{
  if (core)
  {
    core->notifyProcessLeave(*process);
    delete core;
  }

  if (process) delete process;
  if (record) delete record;
}

__attribute__((section(".init_array"))) int (*__init)(int, char **, char **) = init;
__attribute__((section(".fini_array"))) int (*__fini)(void) = fini;
