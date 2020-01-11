#ifndef __PEPPER_TESTING_CORE_CATALOG_H__
#define __PEPPER_TESTING_CORE_CATALOG_H__

#include <pepper/testing/base.hpp>
#include <pepper/testing/core/error.hpp>

#include <vector>
#include <functional>

namespace pepper { namespace testing { namespace core {

  class catalog
  {
    public:
      catalog() = default;
      ~catalog() = default;

    private:
      std::vector<const base::suite *> _suites;

    public:
      void add(const base::suite *suite)
      {
        _suites.push_back(suite);
      }

    public:
      void foreach(const std::function<void (const base::suite *)> &fn) const
      {
        for (auto suite : _suites)
        {
          fn(suite);
        }
      }

    public:
      static catalog &instance(void)
      {
        static catalog obj;

        return obj;
      }
  };

} } }

#endif 
