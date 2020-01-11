#ifndef __PEPPER_UNIT_DESC_H__
#define __PEPPER_UNIT_DESC_H__

#include <core/unit/data.hpp>

namespace core { namespace unit {

  class desc
  {
    private:
      std::unique_ptr<unit::data> _data;

    public:
      const unit::pathname::root &root(void) const;

    public:
      const unit::name &name(void) const;
    public:
      const unit::manifest::spec &manifest(void) const;

    public:
      desc(const boost::filesystem::path &r);
      virtual ~desc() = default;
  };

} }

#endif
