#ifndef __PEPPER_JIMAGE_OBJECT_H__
#define __PEPPER_JIMAGE_OBJECT_H__

#include <pepper/jimage/accessor.hpp>
#include <pepper/jpath.hpp>
#include <pepper/fun.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace jimage {

  class object
  {
    private:
      std::shared_ptr<jimage::accessor> _accessor;

    public:
      object(const std::shared_ptr<jimage::accessor> &accessor);
      object(const object &o);

    public:
      void read(const jpath::object &p, const std::function<void (int)> &fn) const;
      void read(const jpath::object &p, const std::function<void (const std::string &)> &fn) const;

    public:
      void enumerate(const jpath::object &p, const std::function<void (int, const object &)> &fn) const;
  };

} }

#endif
