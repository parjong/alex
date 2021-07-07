#ifndef __PEPPER_FILTER_CHAIN_H__
#define __PEPPER_FILTER_CHAIN_H__

#include <pepper/filter/unit.hpp>
#include <pepper/mem.hpp>

#include <vector>

namespace pepper { namespace filter {

  template <typename T, bool B> struct chain
  {
    private:
      std::vector<std::unique_ptr<filter::unit<T>>> _units;

    public:
      chain<T, B> &append( std::unique_ptr<filter::unit<T>> &&u )
      {
        _units.emplace_back( std::move(u) );
        return *this;
      }

    public:
      bool check(const T &value) const
      {
        for (auto &unit : _units)
        {
          switch ( unit->check(value) )
          {
            case action::DELEGATE:
              continue;

            case action::ACCEPT:
              return true;

            case action::REJECT:
              return false;
          }
        }

        return B;
      }

    public:
      chain() = default;
      ~chain() = default;
  };

} }

#endif
