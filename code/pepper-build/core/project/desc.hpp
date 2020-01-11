#ifndef FORWARD_DECL

#ifndef __PEPPER_BUILD_PROJECT_DESC_H__
#define __PEPPER_BUILD_PROJECT_DESC_H__

#include <core/project/data.hpp>

namespace core { namespace project {

  class desc
  {
    private:
      std::unique_ptr<project::data> _data;

    private:
      const project::pathname::root _root;
    public:
      const project::pathname::root &root(void) const;

    public:
      desc(const boost::filesystem::path &root);
      ~desc() = default; 

    public:
      const core::project::manifest::spec &manifest(void) const;
      const core::unit::ctxt &units(void) const;
  };

} }

#endif // __PEPPER_BUILD_PROJECT_DESC_H__

#else

#ifndef __PEPPER_BUILD_PROJECT_DESC_FORWARD_H__
#define __PEPPER_BUILD_PROJECT_DESC_FORWARD_H__

namespace core { namespace project {

  class desc;

} }

#endif // __PEPPER_BUILD_PROJECT_DESC_FORWARD_H__

#endif
