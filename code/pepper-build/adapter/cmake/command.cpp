#include <adapter/cmake/command.hpp>

namespace adapter { namespace cmake {

  command::command(const std::string &tag)
    : _tag{ tag }
  {
    // DO NOTHING
  }

  void command::dump_into(std::ostream &os) const
  {
    os << _tag;

    switch ( args().size() )
    {
      case 0:
        os << "()";
        break;

      case 1:
        os << "(" << args()[0] << ")";
        break;

      default:
        os << "(" << args()[0];

        for (int i = 1; i < args().size(); ++i)
        {
          os << " " << args()[i];
        }

        os << ")";
        break;
    }

    os << std::endl;
  }

} }
