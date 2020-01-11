#ifndef __PEPPER_APPFW_CLI_ARGS_BLOCK_DESC_H__
#define __PEPPER_APPFW_CLI_ARGS_BLOCK_DESC_H__

#include <pepper/appfw/cli/args/desc.hpp>
#include <pepper/appfw/cli/args/block/cursor.hpp>

namespace pepper { namespace appfw { namespace cli { namespace args { namespace block {

  class desc : public args::desc
  {
    private:
      int _argc;
      char **_argv;

    public:
      desc(int argc, char **argv) : _argc{argc - 1}, _argv{argv + 1}
      {
        // DO NOTHING
      }

    public:
      virtual ~desc() = default;

    public:
      virtual pepper::collection::cursor::bean<std::string> cursor(void) const
      {
        return mem::shared::make<pepper::collection::cursor::object<std::string>, block::cursor>(_argc, _argv);
      }
  };

} } } } }

#endif
