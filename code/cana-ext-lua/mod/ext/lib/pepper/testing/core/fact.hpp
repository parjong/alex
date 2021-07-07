#ifndef __PEPPER_TESTING_CORE_FACT_H__
#define __PEPPER_TESTING_CORE_FACT_H__

#include <pepper/testing/core/catalog.hpp>
#include <pepper/testing/core/suite.hpp>
#include <pepper/testing/base.hpp>

namespace pepper { namespace testing { namespace core {

  class fact : public base::unit
  {
    public:
      fact(core::suite &suite, const std::string &name) : _name{name}
      {
        suite.add(this);
      }

    public:
      virtual ~fact() = default;

    private:
      std::string _name;

    public:
      virtual const std::string name(void) const
      {
        return _name;
      }
  };

} } }
  
#endif
