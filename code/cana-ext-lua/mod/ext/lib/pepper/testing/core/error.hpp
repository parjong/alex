#ifndef __PEPPER_TESTING_CORE_ERROR_H__
#define __PEPPER_TESTING_CORE_ERROR_H__

#include <stdexcept>

namespace pepper { namespace testing { namespace core {

  class error
  {
    private:
      std::string _message;

    public:
      error(const std::string &message) : _message{message}
      {
        // DO NOTHING
      }

      virtual ~error() = default;

    public:
      const std::string &message(void) const
      {
        return _message;
      }
  };

} } }

#endif
