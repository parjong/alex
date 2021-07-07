#include <cana/ext/service.hpp>

#include "app.h"

#include <memory>

extern "C" std::unique_ptr<cana::ext::app> make(const cana::ext::service &svc)
{
  return std::make_unique<app>(svc);
}
