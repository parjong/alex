#ifndef __PEPPER_EXN_OBJECT_H__
#define __PEPPER_EXN_OBJECT_H__

#include <pepper/fmt.hpp>

#include <string>
#include <sstream>

#include <exception>

namespace pepper { namespace exn {

  struct object : public std::exception
  {
    object() = default;
    virtual ~object() = default;

    virtual const char *what(void) const noexcept = 0;
  };

  template <typename... Args> class typed_object : public object
  {
    private:
      std::string _message;

    public:
      typed_object(const Args&... args)
      {
        std::stringstream ss;

        ss << pepper::fmt::make(args...);

        _message = ss.str();
      }
    
    public:
      virtual ~typed_object() = default;

    public:
      virtual const char *what(void) const noexcept
      {
        return _message.c_str();
      }
  };

} } 

#endif
