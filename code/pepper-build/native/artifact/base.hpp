#ifndef __PEPPER_BUILD_ARTIFACT_BASE_H__
#define __PEPPER_BUILD_ARTIFACT_BASE_H__

namespace native { namespace artifact {

  struct visitor;

  struct base
  {
    base() = default;
    virtual ~base() = default;

    virtual void accept(visitor &v) const = 0;
  };

  struct exe : public base
  {
    exe() = default;
    virtual ~exe() = default;

    virtual void accept(visitor &v) const;
  };

  struct lib : public base
  {
    lib() = default;
    virtual ~lib() = default;

    virtual void accept(visitor &v) const;
  };

  struct visitor
  {
    visitor() = default;
    virtual ~visitor() = default;

    virtual void visit(const exe &) = 0;
    virtual void visit(const lib &) = 0;
  };

} }

#endif
