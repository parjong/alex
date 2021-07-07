#ifndef __PEPPER_CMDLINE_DESC_H__
#define __PEPPER_CMDLINE_DESC_H__

#include <pepper/cmdline/action/desc.hpp>
#include <pepper/cmdline/option/desc.hpp>

#include <pepper/mem.hpp>
#include <pepper/dict.hpp>
#include <pepper/optional.hpp>

#include <string>

namespace pepper { namespace cmdline {

  struct desc
  {
    desc() = default;
    virtual ~desc() = default;

    virtual optional::object<action::bean> lookup(const std::string &tag) const = 0;
  };

} }

namespace pepper { namespace cmdline { namespace simple {

  class desc : public cmdline::desc
  {
    public:
      desc() = default;
      virtual ~desc() = default;

    private:
      pepper::dict::object<std::string, std::shared_ptr<option::desc>> _table;

    public:
      option::desc &option(const std::string &tag);
      virtual optional::object<action::bean> lookup(const std::string &tag) const;
  };

} } }

#endif
