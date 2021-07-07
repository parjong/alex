#ifndef __PEPPER_JIMAGE_ACCESSOR_H__
#define __PEPPER_JIMAGE_ACCESSOR_H__

#include <pepper/jpath.hpp>
#include <pepper/fun.hpp>
#include <pepper/mem.hpp>

#include <string>

namespace pepper { namespace jimage {

  struct accessor
  {
    accessor() = default;
    virtual ~accessor() = default;

    virtual void read(const jpath::object &p, const std::function<void (int)> &fn) const = 0;
    virtual void read(const jpath::object &p, const std::function<void (const std::string &)> &fn) const = 0;

    virtual void enumerate(const jpath::object &p, const std::function<void (int, const std::shared_ptr<accessor> &)> &fn) const = 0;
  };

} }

#endif
