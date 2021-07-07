#ifndef __PEPPER_APPFW_CLI_ARGS_BLOCK_CURSOR_H__
#define __PEPPER_APPFW_CLI_ARGS_BLOCK_CURSOR_H__

#include <pepper/collection.hpp>

namespace pepper { namespace appfw { namespace cli { namespace args { namespace block {

  class cursor : public pepper::collection::cursor::object<std::string>
  {
    private:
      int _end;
      char **_cur;

    public:
      cursor(int end, char **cur) : _end{end}, _cur{cur}
      {
        // DO NOTHING
      }

      virtual ~cursor() = default;

    public:
      virtual maybe::object<std::string> access(unsigned off) const
      {
        if (_end <= off)
        {
          return maybe::none<std::string>();
        }

        return maybe::some<std::string>(_cur[off]);
      }

    public:
      virtual void forward(unsigned off)
      {
        _end -= off;
        _cur += off;
      }
  };

} } } } }

#endif
