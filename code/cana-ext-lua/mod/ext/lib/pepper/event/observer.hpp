#ifndef __PEPPER_EVENT_OBSERVER_H__
#define __PEPPER_EVENT_OBSERVER_H__

namespace pepper { namespace event {

  template <typename T> struct observer
  {
    observer() = default;
    virtual ~observer() = default;

    virtual void notify(const T &) = 0;
  };

} }

#endif
