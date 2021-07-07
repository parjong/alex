#include <pepper/optparse/parser.hpp>

#include <boost/algorithm/string/predicate.hpp>

namespace pepper { namespace optparse {

  void parser::add_longopt(const std::string &tag, opt::base &opt)
  {
    _long_options[tag] = &opt;
  }

  void parser::parse(pepper::stream::base<std::string> &s) const
  {
    while ( true )
    {
      auto arg = s.lookup(0);

      if ( !arg )
      {
        return;
      }

      const auto &head = arg.get();

      if ( boost::algorithm::starts_with(head, "--") )
      {
        // Case 1. Long-option
        auto it = _long_options.find( head.substr(2) );

        if ( it == _long_options.end() )
        {
          // Unsupported option
          return;
        }        

        s.forward(1);
        it->second->take(s);
        continue;
      } 
          
      // Unknown arugments
      return;      
    }   
  }

} }
