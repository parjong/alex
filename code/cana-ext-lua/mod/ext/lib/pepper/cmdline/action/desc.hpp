#ifndef __PEPPER_CMDLINE_ACTION_DESC_H__
#define __PEPPER_CMDLINE_ACTION_DESC_H__

#include <pepper/cmdline/reader.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace cmdline { namespace action {

  struct desc
  {
    desc() = default;
    virtual ~desc() = default;

    virtual unsigned int perform(const pepper::cmdline::reader &r) = 0;
  };

  class bean
  {
    private:
      std::shared_ptr<action::desc> _ptr;

    public:
      bean(const std::shared_ptr<action::desc> &ptr)
      {
        _ptr = ptr;
      }

    public:
      ~bean() = default;

    public:
      unsigned int perform(const pepper::cmdline::reader &r) const
      {
        return _ptr->perform(r);
      } 
  };

} } }

#endif
