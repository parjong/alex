#ifndef __PEPPER_TESTING_CORE_SUITE_H__
#define __PEPPER_TESTING_CORE_SUITE_H__

#include <pepper/testing/base.hpp>

#include <functional>
#include <vector>

namespace pepper { namespace testing { namespace core {

  class suite : public base::suite
  {
    private:
      std::string _name;

    public:
      suite(const std::string &name) : _name{name}
      {
        catalog::instance().add(this);
      }

    public:
      virtual ~suite() = default;

    private:
      std::vector<const base::unit *> _units;
    
    public:
      void add(const base::unit *unit)
      {
        _units.push_back(unit);
      }

    public:
      virtual const std::string name(void) const
      {
        return _name;
      }

      virtual void foreach(const std::function<void (const base::unit *)> &fn) const
      {
        for (auto unit : _units)
        {
          fn(unit);
        }
      }
  };

} } }

#endif
