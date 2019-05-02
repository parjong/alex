#ifndef __CLEO_SERVICE_H__
#define __CLEO_SERVICE_H__

namespace cleo
{

// Each app can expose its service to descendants
struct Service
{
  virtual ~Service() = default;
};

} // namespace cleo

#endif // __CLEO_SERVICE_H__
