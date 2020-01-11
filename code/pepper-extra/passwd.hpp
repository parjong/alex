#ifndef __PEPPER_PASSWD_H__
#define __PEPPER_PASSWD_H__

#include <string>

namespace pepper { namespace passwd {

  struct reader 
  {
    reader() = default;
    virtual ~reader() = default;

    virtual std::string read(const std::string &prompt) = 0;
  };

  class unix_reader : public reader
  {
    public:
      unix_reader() = default;
      virtual ~unix_reader() = default;

    public:
      virtual std::string read(const std::string &prompt);      
  };

} }

#endif
