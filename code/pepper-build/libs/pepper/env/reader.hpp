#ifndef __PEPPER_ENV_READER_H__
#define __PEPPER_ENV_READER_H__

#include <pepper/maybe.hpp>
#include <pepper/functional.hpp>

#include <string>

namespace pepper { namespace env {

  class reader : public pepper::maybe::reader<std::string>
  {
    private:
      const std::string _name;

    public:
      reader(const std::string &name);
      ~reader() = default;

    public:
      virtual bool filled(void) const;
      virtual bool read(const probe &p) const;
  };

} }

#endif
