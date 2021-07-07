#ifndef __PEPPER_OPTPARSE_PARSER_H__
#define __PEPPER_OPTPARSE_PARSER_H__

#include <pepper/optparse/opt/base.hpp>

#include <map>

namespace pepper { namespace optparse {
 
  class parser
  {
    public:
      parser() = default;
      virtual ~parser() = default;

    private:
      std::map<std::string, opt::base *> _long_options;
    public:
      void add_longopt(const std::string &tag, opt::base &opt);

    public:
      void parse(pepper::stream::base<std::string> &s) const;
  };

} }

#endif
