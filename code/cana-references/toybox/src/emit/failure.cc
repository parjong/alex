#include "failure.h"

Failure::Failure() { }

Failure::Failure(const hiberlite::sqlid_t& cmd, const std::string& opt)
  : cmd_(cmd), opt_(opt)
{
  // Do NOTHING
}

Failure::~Failure()
{

}

const hiberlite::sqlid_t& Failure::cmd(void) const
{
  return cmd_;
}
const std::string& Failure::opt(void) const
{
  return opt_;
}

HIBERLITE_EXPORT_CLASS(Failure);
