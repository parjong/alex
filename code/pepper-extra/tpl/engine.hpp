#ifndef __PEPPER_TPL_ENGINE_H__
#define __PEPPER_TPL_ENGINE_H__

#include "pepper/subst.hpp"

#include "pepper/fs.hpp"
#include "pepper/pathname/glob.hpp"
#include "pepper/owned.hpp"

namespace pepper { namespace tpl { namespace action {

  namespace fs = boost::filesystem;

  struct base
  {
    base() = default;
    virtual ~base() = default;

    virtual void perform(const pepper::subst &, const fs::path &src, const fs::path &dst) const = 0;
  };

  class copy : public base
  {
    public:
      copy() = default;
      virtual ~copy() = default;

    public:
      virtual void perform(const pepper::subst &, const fs::path &src, const fs::path &dst) const;
  };

  class rewrite : public base
  {
    public:
      rewrite() = default;
      virtual ~rewrite() = default;

    public:
      virtual void perform(const pepper::subst &, const fs::path &src, const fs::path &dst) const;
  };

  class ignore : public base
  {
    public:
      ignore() = default;
      virtual ~ignore() = default;

    public:
      virtual void perform(const pepper::subst &, const fs::path &src, const fs::path &dst) const;
  };

}

} }

namespace pepper { namespace tpl {

  namespace fs = boost::filesystem;

  class engine
  {
    private:
      pepper::subst _subst;
      const action::base &_action;

    public:
      engine(const pepper::dict::base &dict, const action::base &action);
      ~engine() = default;
    
    private:
      std::vector<std::pair<const pepper::pathname::glob *, const action::base *>> _actions;
    public:
      void add_action(const pepper::pathname::glob &glob, const action::base &action);
    private:
      const action::base &find_action(const fs::path &path);

    public:
      bool create(const fs::path &src, const fs::path &dst);
  };

} } 

#endif
