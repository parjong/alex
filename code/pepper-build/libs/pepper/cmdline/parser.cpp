#include <pepper/cmdline/parser.hpp>

namespace pepper { namespace cmdline {

  bool parser::parse(cmdline::cursor &acc)
  {
    auto find_fn = [&] (const std::string &head)
    {
      return _desc.lookup(head);
    };

    while ( true )
    {
      pepper::optional::object<std::string> head = acc.access(0);

      if ( !head.filled() )
      {
        // No more command-line argument
        break;
      }

      auto desc = head.map<action::bean>(find_fn);

      if ( !desc.filled() )
      {
        // Cannot find option description
        return true;
      }

      // Consume the head
      acc.forward(1);

      auto perform_fn = [&] (const action::bean &act)
      {
        return act.perform(acc);
      };

      unsigned int off = desc
        .map<unsigned int>(perform_fn)
        .get(0);

      acc.forward(off);
    }

    return false;
  }

  parser::parser(const pepper::cmdline::desc &desc) : _desc(desc)
  {
    // DO NOTHING
  }

} }
