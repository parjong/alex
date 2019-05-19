#define XRAY_TRACER
#include <xray.h>
#undef XRAY_TRACER

#include <domain.example.h>

#include <iostream>

namespace
{

std::string event_description(const xray::EventHnd *hnd)
{
  auto p = hnd->domain->what(hnd->index);
  return (nullptr == p) ? "(unknown)" : *p;
}

} // namespace

namespace xray
{

void endpoint::post(const EventHnd *hnd)
{
  std::cout << "hnd.domain: " << hnd->domain << std::endl;
  std::cout << "hnd.index:" << hnd->index << std::endl;
  std::cout << "evt.what: " << event_description(hnd) << std::endl;

  if (hnd->domain == MyDomain::get())
  {
    const auto &evt = MyDomain::get()->event(hnd->index);
    std::cout << evt._msg << std::endl;
  }
}

} // namespace xray

int init_endpoint(void)
{
  return 0;
}
