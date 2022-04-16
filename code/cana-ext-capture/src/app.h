#ifndef __CAPTURE_APP_H__
#define __CAPTURE_APP_H__

#include <cana/ext/app.hpp>
#include <cana/ext/service.hpp>
#include <cana/proc/info.hpp>

class app : public cana::ext::app
{
  private:
    std::shared_ptr<cana::ext::storage> _storage;

  public:
    app(const cana::ext::service &s);

  public:
    virtual void notifyProcessEnter(const cana::proc::info &pi);
    virtual void notifyProcessLeave(const cana::proc::info &pi);
};

#endif
