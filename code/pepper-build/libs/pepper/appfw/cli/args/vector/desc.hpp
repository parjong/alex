#ifndef __PEPPER_APPFW_CLI_ARGS_VECTOR_DESC_H__
#define __PEPPER_APPFW_CLI_ARGS_VECTOR_DESC_H__

#include <pepper/appfw/cli/args/desc.hpp>
#include <pepper/vector.hpp>

namespace pepper { namespace appfw { namespace cli { namespace args { namespace vector {

  class desc : public args::desc
  {
    private:
      pepper::vector::object<std::string> _vec;

    public:
      desc() = default;
      virtual ~desc() = default;

    public:
      desc &emplace(const std::string &arg)
      {
        _vec.emplace(arg);
        return *this;
      }

    public:
      std::size_t size(void) const
      {
        return _vec.size();
      }

    public:
      virtual pepper::collection::cursor::bean<std::string> cursor(void) const
      {
        return _vec.collection().cursor();
      }
  };  

} } } } }

#endif
