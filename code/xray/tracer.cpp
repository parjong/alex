#define XRAY_TRACER
#include <xray.h>
#undef XRAY_TRACER

#include <endpoint.h>
#include <iostream>

#include <dlfcn.h>

#if 0
// TODO Find how to override "endpoint" weak symbol with an implementation in a linked library
namespace xray
{

void post(const EventHnd &evt)
{
  std::cout << evt.index << std::endl;
}

} // namespace xray
#endif

typedef void (*entry_fn)(void);

int main(int argc, char **argv)
{
  // "post" function is inaccesible from tracee without this function call
  init_endpoint();

  auto handle = dlopen(argv[1], RTLD_LAZY | RTLD_GLOBAL);
  auto entry = reinterpret_cast<entry_fn>(dlsym(handle, "entry"));
  
  std::cout << "Call entry from tracer" << std::endl;
  entry();
  std::cout << "Call entry from tracer - done" << std::endl;

  return 0;
}
