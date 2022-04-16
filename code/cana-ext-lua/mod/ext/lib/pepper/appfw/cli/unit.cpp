#include <pepper/appfw/cli/unit.hpp>

#include <pepper/appfw/cli/option/set.hpp>
#include <pepper/appfw/cli/command/set.hpp>

#include <pepper/appfw/cli/service/exitcode/impl.hpp>
#include <pepper/appfw/cli/service/cmdline/impl.hpp>
#include <pepper/appfw/cli/service/impl.hpp>

#include <pepper/cmdline.hpp>
#include <pepper/bucket.hpp>
#include <pepper/attr.hpp>

#include <iostream>

namespace {
  
  struct action : public pepper::cmdline::action::desc
  {
    pepper::attr::value::accessor<std::vector<pepper::appfw::app::option::desc *>> observers;
    
    virtual unsigned int perform(const pepper::cmdline::reader &r) 
    {
      auto notify_fn = [&] (const std::string &value)
      {
        for (auto observer : observers())
        {
          (*observer).notify( value );
        }
      };

      r.access(0).read(notify_fn);

      return 1;
    }

    action() = default;
    virtual ~action() = default;
  };

  pepper::cmdline::desc &emplace(pepper::cmdline::simple::desc &cmdline_desc, 
      const pepper::bucket::object<std::string, pepper::appfw::app::option::desc *> &option_bucket)
  {
    auto each_fn = [&] (const std::string &key, const pepper::collection::object<pepper::appfw::app::option::desc *> &ds)
    {
      auto act = pepper::mem::shared::make<::action>();

      pepper::collection::foreach(ds) << [&] (pepper::appfw::app::option::desc *option_desc)
      {
        (*act).observers().emplace_back( option_desc );
      };

      cmdline_desc.option(key).action(act);
    };

    option_bucket.foreach(each_fn);

    return cmdline_desc;
  }

}
namespace pepper { namespace appfw { namespace cli {

  unit::unit(const std::shared_ptr<pepper::appfw::app::desc> &app)
  {
    _app = app;
  }

  app::desc &unit::app(void)
  {
    return *(_app);
  }

  pepper::optional::object<int> unit::invoke(pepper::collection::cursor::bean<std::string> &cur)
  {
    pepper::bucket::object<std::string, pepper::appfw::app::option::desc *> option_bucket;

    // Enroll 'option'(s) from 'app'
    pepper::appfw::cli::option::set option_set{ option_bucket };

    app().enroll( option_set );

    // Create a command-line description
    pepper::cmdline::simple::desc cmdline_desc;

    ::emplace( cmdline_desc, option_bucket );

    // Create a command-line parser
    pepper::cmdline::parser cmdline_parser{ cmdline_desc };

    // Parse the command-line
    cmdline_parser.parse( cur.object() );

    //
    pepper::optional::object<int> code;

    // Create a service
    pepper::appfw::cli::service::exitcode::impl   exitcode{ code  };
    pepper::appfw::cli::service::cmdline::impl    cmdline{ cur };
    pepper::appfw::cli::service::impl             service{ exitcode, cmdline };

    // Invoke an application
    app().invoke( service );

    return code;
  }
 
  void unit::usage(std::ostream &os)
  {
    // Enroll 'option'(s) from 'app'
    pepper::bucket::object<std::string, pepper::appfw::app::option::desc *> option_bucket;

    pepper::appfw::cli::option::set option_set{ option_bucket };

    app().enroll( option_set );

    if (option_bucket.size() > 0)
    {
      os << "AVAILABLE OPTION:" << std::endl;
      auto show_fn = [&] (const std::string &tag, const pepper::collection::object<pepper::appfw::app::option::desc *> &values)
      {
        os << "  " << tag << std::endl;
      };
      option_bucket.foreach(show_fn);
    }

    pepper::appfw::cli::command::set::dict cdict;

    // Enroll 'command' from 'app'
    pepper::appfw::cli::command::set cset{ cdict };

    app().enroll( cset );

    os << "AVAILABLE COMMAND:" << std::endl;
    auto show_fn = [&] (const std::string &tag, const std::shared_ptr<pepper::appfw::app::desc> &app)
    {
      os << "  " << tag << std::endl;
    };
    cdict.foreach(show_fn);
  }

  pepper::maybe::object<std::shared_ptr<pepper::appfw::app::desc>> unit::lookup(const std::string &tag)
  {
    pepper::appfw::cli::command::set::dict command_dict;

    // Enroll 'command' from 'app'
    pepper::appfw::cli::command::set command_set{ command_dict };

    app().enroll( command_set );

    // Lookup an appropriate 'app'
    return command_dict.lookup(tag);
  }

} } }
