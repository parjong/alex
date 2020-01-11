#ifndef __PEPPER_BUILD_CORE_FWK_BOX_H__
#define __PEPPER_BUILD_CORE_FWK_BOX_H__

#include <core/fwk/name.hpp>
#include <core/fwk/table.hpp>
#include <core/fwk/base.hpp>

#include <pepper/mem.hpp>

namespace core { namespace fwk {

  class box
  {
    private:
      fwk::table &_table;
      std::unique_ptr<fwk::base> _base;

    public:
      box(fwk::table &tbl, std::unique_ptr<fwk::base> &&base) : _table( tbl ), _base{ std::move(base) }
      {
        // DO NOTHING
      }

    public:
      ~box() = default;

    public:
      box &name(const std::string &k)
      {
        _table[k] = _base.get();
        return *this;
      }
  };


} }

#endif
