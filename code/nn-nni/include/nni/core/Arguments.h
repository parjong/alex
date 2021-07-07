#ifndef __NNI_CORE_ARGUMENTS_H__
#define __NNI_CORE_ARGUMENTS_H__

struct Arguments
{
  virtual ~Arguments() = default;

  virtual uint32_t size(void) const = 0;
  virtual const char *at(uint32_t n) const = 0;
};

#endif // __NNI_CORE_ARGUMENTS_H__
