#ifndef __PEPPER_BUILD_UNIT_DATA_H__
#define __PEPPER_BUILD_UNIT_DATA_H__

#ifdef FORWARD_DECL
#include <core/project/desc.hpp>
#endif
#include <core/unit/name.hpp>
#include <core/unit/pathname/root.hpp>
#include <core/unit/manifest/spec.hpp>

#include <pepper/attr.hpp>

namespace core { namespace unit {

  class data 
  {
    private:
      const unit::pathname::root _root;
    public:
      const unit::pathname::root &root(void) const;

    public:
      pepper::attr::lazy::reader<unit::manifest::spec> manifest;
      pepper::attr::lazy::reader<unit::name> name;

    public:
      data(const boost::filesystem::path &base);
      virtual ~data() = default;
  };

} }

#endif
