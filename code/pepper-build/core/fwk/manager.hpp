#ifndef __PEPPER_BUILD_CORE_FWK_CTXT_H__
#define __PEPPER_BUILD_CORE_FWK_CTXT_H__

#include <core/fwk/box.hpp>
#include <core/fwk/base.hpp>
#include <core/fwk/name.hpp>
#include <core/fwk/table.hpp>

#include <pepper/attr.hpp>
#include <pepper/mem.hpp>

#include <vector>
#include <string>
#include <memory>

namespace core { namespace fwk {

  class manager
  {
    private:
      fwk::table _table;
      
    private:
      std::vector<std::unique_ptr<fwk::box>> _boxes;

    public:
      fwk::box &add(std::unique_ptr<fwk::base> &&fwk)
      {
        return **_boxes.emplace( _boxes.end(), new fwk::box{ _table, std::move(fwk) } );
      }

    public:
      const fwk::base *lookup(const fwk::name &k) const
      {
        auto it = _table.find( k.string() );

        if ( it == _table.end() )
        {
          return nullptr;
        }

        return it->second;
      }

    public:
      manager() = default;
      ~manager() = default;
  };

} }

#endif
