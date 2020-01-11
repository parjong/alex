#ifndef __PEPPER_CMDLINE_PARSER_H__
#define __PEPPER_CMDLINE_PARSER_H__

#include <pepper/cmdline/cursor.hpp>
#include <pepper/cmdline/desc.hpp>

namespace pepper { namespace cmdline {

  class parser
  {
    private:
      const pepper::cmdline::desc &_desc;

    public:
      bool parse(cmdline::cursor &acc);

    public:
      parser(const pepper::cmdline::desc &desc);
      ~parser() = default;
  };

} }

#endif
