#ifndef __PEPPER_CLI_APP_BASE_H__
#define __PEPPER_CLI_APP_BASE_H__

#include "pepper/cli/option/base.hpp"
#include "pepper/cli/option/typed.hpp"

#include "pepper/owned.hpp"
#include "pepper/stream.hpp"

#include "pepper/logging/logger.hpp"

namespace pepper { namespace cli { namespace cmd {

  class base
  {
    private:
      const app::base &_parent;
      const std::string _name;

    public:
      base(const app::base &parent, const std::string &name);
      ~base() = default;

    private:
      bool _visible;
    public:
      base &show(void);
      base &hide(void);
    public:
      bool is_visible(void) const;

    private:
      std::string _desc;      
    public:
      base &desc(const std::string &d);
      const std::string &desc(void) const;

    private:
      pepper::owned::ptr<app::base> _app;
    public:
      base &set(app::base *app);

    public:
      void run(stream::base &ts);
  };

} } }

namespace pepper { namespace cli { namespace app {

  struct type
  {
    type() = default;
    virtual ~type() = default;

    virtual void show_header(std::ostream &os) const = 0;
  };

  /**
   * An CLI Application (which may have options)
   */
  class base
  {    
    private:
      static pepper::logging::logger _log;
     
    public:
      base() = default;
      virtual ~base() = default;
 
    private:     
      pepper::owned::ptr<type> _head;
    public:
      void head(type *t);
      const type &head(void) const;

    // NAME
    public:
      virtual const std::string &name(void) const = 0;

    /**
     * Option(s)
     */
    private:
      // TODO Let's implement pepper::weak library
      std::map<std::string, option::base *> _options;
    public:
      void add_option(option::base &opt);

    public:
      std::size_t count_options(void) const;

    /**
     * Command(s)
     */ 
    private:
      pepper::owned::table<cmd::base> _commands;
    public:
      cmd::base &command(const std::string &tag);
    private:
      size_t count_commands(void) const;
      
    private:
      void parse_options(stream::base &ts);
      void parse_command(stream::base &ts);

    private:
      virtual void main(stream::base &ts) = 0;

    private: 
      virtual void show_args(std::ostream &os) const = 0;
      void show_usage(std::ostream &os) const;
      void show_description(std::ostream &os) const;
      void show_options(std::ostream &os) const;
      void show_commands(std::ostream &os) const; 
    private:
      void error(const std::runtime_error &e) const;

    public:
      void run(stream::base &ts);
  }; 

  /**
   * CLI Application without argument
   */
  class nonarg : public base
  {
    private:
      const std::string _name;

    public:
      nonarg(const std::string &name);
      virtual ~nonarg() = default;

    public:
      virtual const std::string &name(void) const;

    private:
      virtual void show_args(std::ostream &os) const;
      virtual void main(stream::base &ts);
  };

  /**
   *
   */
  class toplevel : public type
  {
    private:
      std::string _name;

    public:
      toplevel(const std::string &name);
      virtual ~toplevel() = default;

    public:
      virtual void show_header(std::ostream &os) const;
  };

  class child : public type  
  {
    private:
      const base &_parent;
      std::string _name;

    public:
      child(const base &parent, const std::string &name);
      virtual ~child() = default;

    public:
      virtual void show_header(std::ostream &os) const;
  };

} } }

#endif
