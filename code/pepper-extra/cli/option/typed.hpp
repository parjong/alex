#ifndef __PEPPER_CLI_TYPED_OPTION_H__
#define __PEPPER_CLI_TYPED_OPTION_H__

#include "pepper/cli/option/base.hpp"

#include "pepper/owned.hpp"
#include "pepper/stream.hpp"
#include "pepper/except.hpp"
#include "pepper/logging.hpp"

#include <boost/lexical_cast.hpp>

namespace pepper { namespace cli { namespace quantifier {

  template <typename T> struct base
  {
    base() = default;
    virtual ~base() = default;

    virtual bool member(const T &value) const = 0;    
    virtual void iter(std::function<void (const T &)> fn) const = 0;
  };

} } }

namespace pepper { namespace cli { namespace option {

  template <typename T> class unary : public base
  {
    public:
      unary(pepper::cli::app::base &cmd, const std::string &head, const std::string &desc)
        : base{ cmd, head, desc }
      {
        // DO NOTHING
      }
    public:
      virtual ~unary() = default;

    private:
      pepper::owned::ptr< quantifier::base<T> > _quantifier;
    public:
      void quantifier(quantifier::base<T> *q)
      {
        _quantifier.set( q );
      }

    private:
      virtual void value(const T &value) = 0;
    public:
      virtual void take(stream::base &ts)
      {
        boost::optional<std::string> tok = ts.next();

        if ( !tok )
          pepper::throw_exn( "%s requires an argument, but not provided", head() );

        T v = boost::lexical_cast<T>( tok.get() );

        if ( _quantifier && ! _quantifier->member(v) )
          pepper::throw_exn( "%s is not supported", v );

        value( v );
      }

    public:
      virtual void show_values(std::ostream &os) const
      {
        if ( ! _quantifier )
        {
          return;
        }

        auto show_fn = [&] (const T &value)
        {
          os << value << std::endl;
        };

        _quantifier->iter( show_fn );
      }
  };

  template <typename T> class must : public unary<T>
  {    
    public:
      must(pepper::cli::app::base &cmd, const std::string &head, const std::string &desc)
        : unary<T>{ cmd, head, desc + " (mandatory)" }
      {
        // DO NOTHING
      }
      virtual ~must() = default;

    private:
      bool is_initialized(void) const
      {
        return (bool) _value;
      }

    public:
      const T &operator()(void) const 
      { 
        return *_value; 
      }

    private:
      boost::optional<T> _value;

      virtual void value(const T &v)
      {
        _value = v;
      }

    public:
      virtual void check(void) const 
      {
        if ( !is_initialized() )
          pepper::throw_exn( "%s is required, but not provied", this->head() );  
      };
  };

  template <typename T> class may : public unary<T>
  {
    public:
      may(pepper::cli::app::base &cmd, const std::string &head, const std::string &desc)
        : unary<T>{ cmd, head, desc + " (optional)" }
      {
        // DO NOTHING
      }
      virtual ~may() = default;

    public:
      const boost::optional<T> &operator()(void) const 
      { 
        return _value; 
      }

    private:
      boost::optional<T> _value;

      virtual void value(const T &v)
      {
        _value = v;
      }

    public:
      virtual void check(void) const { return; }
  };

} } }

#endif
