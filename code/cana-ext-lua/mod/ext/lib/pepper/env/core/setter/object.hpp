#ifndef __PEPPER_ENV_CORE_SETTER_OBJECT_H__
#define __PEPPER_ENV_CORE_SETTER_OBJECT_H__

#include <pepper/env/core/setter/spec.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace env { namespace core { namespace setter {

  class object
  {
    private:
      std::shared_ptr<setter::spec> _ptr;

    public:
      object(const std::shared_ptr<setter::spec> &ptr) : _ptr{ptr}
      {
        // DO NOTHING
      }
    
    public:
      ~object() = default;

    public:
      object &operator=(const std::string &value)
      {
        _ptr->set(value);
      }
  };

} } } }

#endif
