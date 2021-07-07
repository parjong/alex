#ifndef __NNC_CORE_MODULE_H__
#define __NNC_CORE_MODULE_H__

class Module
{
public:
  Module() = default;

public:
  Module(const Module &) = delete;
  Module(Module &&) = delete;
};

#endif // __NNC_CORE_MODULE_H__
