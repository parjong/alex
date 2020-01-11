#include "pepper/cli/app/base.hpp"
#include "pepper/cli/log.hpp"

#include <iostream>

namespace pepper { namespace cli { namespace cmd {

  /**
   * Command
   */
  base::base(const app::base &parent, const std::string &name)
    : _parent( parent )
    , _name{ name }
    , _visible{ true }
  {
    // DO NOTHING
  }

  bool base::is_visible(void) const 
  {
    return _visible;
  }

  base &base::show(void)
  {
    _visible = true;

    return *this;
  }

  base &base::hide(void)
  {
    _visible = false;

    return *this;
  }

  base &base::desc(const std::string &d)
  {
    _desc = d;

    return *this;
  }

  const std::string &base::desc(void) const
  {
    return _desc;
  }
  
  base &base::set(app::base *app)
  {
    app->head( new app::child{ _parent, _name } );

    _app.set( app );

    return *this;
  }

  void base::run(stream::base &ts)
  {
    if ( _app ) 
    {
      _app->run(ts);
    }
  }

} } }

namespace pepper { namespace cli { namespace app {

  pepper::logging::logger base::_log{ pepper::cli::log, "base" };

  /**
   *
   */
  void base::head(type *t)
  {
    _head.set( t );
  }

  const type &base::head(void) const
  {
    return *( _head.get() );
  }

  /**
   * Option(s)
   */
  void base::add_option(option::base &opt)
  {
    _options[opt.head()] = &opt;
  }

  std::size_t base::count_options(void) const
  {
    return _options.size();
  }

  /**
   * Command(s)
   */
  cmd::base &base::command(const std::string &name) 
  {    
    cmd::base *cmd = new cmd::base{ *this, name };
   
    _commands.insert( name, cmd );

    return *cmd;
  }

  size_t base::count_commands(void) const
  {
    return _commands.size();
  }

  /**
   *
   */
  void base::parse_options(stream::base &ts)
  {
    static pepper::logging::logger log{ _log, __func__ };

    while ( ts.lookup(0) )
    {
      boost::optional<std::string> head = ts.lookup(0);
    
      log.info( "visit '%s'", head.get() );

      auto it = _options.find(head.get());

      if ( it == _options.end() )
      {
        log.info( "encounter unknown option '%s'", head.get() );
        break;
      }

      ts.forward(1);
      it->second->take(ts);      
    }    

    for (auto it = _options.begin(); it != _options.end(); ++it)
    {
      it->second->check();
    }
  }

  void base::parse_command(stream::base &ts)
  {
    static pepper::logging::logger log{ _log, __func__ };

    auto res = ts.lookup(0);

    if ( !res ) 
    {
      main(ts);
      return;
    }

    const std::string tag{ res.get() };
   
    if ( !_commands.is_member(tag) )
    {
      main(ts);
      return;
    }

    ts.next();

    _commands.lookup(tag).run(ts);
  }
 
  /**
   *
   */
  void base::show_usage(std::ostream &os) const
  {
    os << "USAGE: " << std::endl;

    // Emit padding
    os << std::string(2, ' ');
    
    // Emit heading
    head().show_header(os);

    if ( count_options() > 0 )
      os << " [OPTIONS]";

    if ( count_commands() > 0 )
      os << " [COMMAND]";

    show_args(os);

    os << std::endl; 

    // Emit newline
    os << std::endl;
  }

  void base::show_description(std::ostream &os) const
  {
    os << name() << std::endl;
    os << std::endl;
  }
    
  void base::show_options(std::ostream &os) const
  {
    if ( count_options() == 0 ) 
    {
      return;
    }

    os << "OPTIONS:" << std::endl;

    size_t name_width = 0;

    // Calculate the maximum name width
    for (auto it = _options.begin(); it != _options.end(); ++it)
    {
      const auto &name = it->first;

      if ( name.size() > name_width )
        name_width = name.size();
    }

    for (auto it = _options.begin(); it != _options.end(); ++it)
    {
      const auto &name = it->first;

      const std::string pad{ 2, ' ' };

      os << pad;
      os << name << std::string( name_width - name.size(), ' ');
      os << "\t";
      it->second->show_desc(os);
      os << std::endl;

      std::stringstream ss;

      it->second->show_values(ss);

      std::string line;

      auto print_fn = [&] (const std::string &msg)
      {
        os << pad << std::string( name_width , ' ') << "\t" << msg << std::endl;;
      };

      while (ss >> line)
      {
        print_fn("  " + line);
      }
    }

    os << std::endl;
  }

  void base::show_commands(std::ostream &os) const
  {
    // TODO Show only when there is more than one visible command
    if ( count_commands() == 0 )
    {
      return;
    }

    os << "COMMANDS:" << std::endl;

    size_t name_width = 0;

    // Calculate the max width of names
    auto size_fn = [&] (const std::string &name, const cmd::base &c)
    {
      if ( c.is_visible() && name.size() > name_width )
        name_width = name.size();
    };

    _commands.iter(size_fn);

    // Show each command
    auto show_fn = [&] (const std::string &name, const cmd::base &c)
    {
      if ( !c.is_visible() )
        return;

      os << std::string(2, ' ') << name << std::string( name_width - name.size(), ' ') << "\t";
      os << c.desc();
      os << std::endl;
    };

    _commands.iter(show_fn);

    os << std::endl;
  }

  void base::error(const std::runtime_error &err) const
  {
    std::cerr << "[ERROR] " << err.what() << std::endl;
    std::cerr << std::endl;

    show_description(std::cerr);
    show_usage(std::cerr);
    show_options(std::cerr);    
    show_commands(std::cerr);

    exit(255);
  }

  /**
   *
   */
  void base::run(stream::base &ts)
  {
    static pepper::logging::logger log{ _log, __func__ };

    try
    {
      parse_options(ts);
      parse_command(ts);
    }
    catch (const std::runtime_error &e)
    {
      error(e);
      exit(255);
    }
  }

  /**
   *
   */
  nonarg::nonarg(const std::string &name)
    : _name{ name }
  {
    // DO NOTHING
  }

  const std::string &nonarg::name(void) const
  {
    return _name;
  }

  void nonarg::show_args(std::ostream &os) const
  {
    return;
  }

  void nonarg::main(stream::base &ts)
  {
    auto res = ts.next();

    if ( !res ) 
    {
      pepper::throw_exn("COMMAND should be provided");
    }

    const std::string tag{ res.get() };

    pepper::throw_exn("%s is not supported", tag);
  }

  /**
   *
   */
  toplevel::toplevel(const std::string &name)
    : _name{ name }
  {
    // DO NOTHING
  }

  void toplevel::show_header(std::ostream &os) const
  {
    os << _name;
  }

  /**
   *
   */
  child::child(const base &parent, const std::string &name)
    : _parent( parent )
    , _name{ name }
  {
    // DO NOTHING
  }

  void child::show_header(std::ostream &os) const
  {
    _parent.head().show_header(os);

    if ( _parent.count_options() > 0 )
      os << " [OPTIONS]";

    os << " " << _name;
  }


} } }
