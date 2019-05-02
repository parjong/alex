#ifndef __CLEO_ARGS_H__
#define __CLEO_ARGS_H__

#include <cstdint>
#include <string>

namespace cleo
{

struct Args
{
  virtual ~Args() = default;

  virtual uint32_t count(void) const = 0;
  virtual std::string value(uint32_t n) const = 0;
};

} // namespace cleo

#endif // __CLEO_ARGS_H__
