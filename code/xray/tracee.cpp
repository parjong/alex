#include <xray.h>
#include <domain.example.h>

#include <iostream>

extern "C" void entry(void)
{
  if (xray::endpoint::post != nullptr)
  {
    std::cout << "Endpoint is existing!" << std::endl;
    xray::EventHnd evt;

    evt.domain = MyDomain::get();
    evt.index = MyDomain::get()->create("Hey");;

    xray::endpoint::post(&evt);
  }
  else
  {
    std::cout << "Endpoint is missing" << std::endl;
  }

  return;
}
