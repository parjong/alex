#include <pepper/appfw/cli/host.hpp>
#include <pepper/appfw/cli/unit.hpp>
#include <pepper/appfw/cli/trail.hpp>

#include <iostream>

namespace pepper { namespace appfw { namespace cli {

  host::host(const std::shared_ptr<pepper::appfw::app::desc> &app) : _app{app}
  {
    // DO NOTHING
  }

  int host::run(const pepper::appfw::cli::args::desc &args)
  {
    auto cursor = args.cursor();

    trail trail;
    unit  unit = trail.push(_app);

    int res = 255;

    while ( true )
    {
      auto code = unit.invoke(cursor);

      auto set_fn = [&] (const int &exitcode)
      {
        res = exitcode;
      };

      // Return if exitcode is provided
      if ( code.read(set_fn) )
      {
        break;
      }

     // Lookup command
      auto found_fn = [&] (const std::string &tag)
      {
        auto valid_fn = [&] (const std::shared_ptr<app::desc> &app)
        {
          unit = trail.push(app);
          return true;
        };

        auto invalid_fn = [&] (void)
        {
          std::cerr << "ERROR: " << tag << " is invalid" << std::endl;
          std::cerr << std::endl;
          unit.usage(std::cerr);
          return false;
        };
 
        pepper::optional::object<std::shared_ptr<pepper::appfw::app::desc>> desc{unit.lookup(tag)};

        return desc.join<bool>(valid_fn, invalid_fn);
      };

      auto notfound_fn = [&] (void)
      {
        std::cerr << "ERROR: No command found" << std::endl;
        std::cerr << std::endl;
        unit.usage(std::cerr);
        return false;
      };

      pepper::optional::object<std::string> curr = cursor.access(0);

      if ( !curr.join<bool>(found_fn, notfound_fn) )
      {
        break;
      }

      // Skip the command
      cursor.forward(1);
    }
   
    return res;
  }

} } }
