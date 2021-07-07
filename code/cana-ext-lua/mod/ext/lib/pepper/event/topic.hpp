#ifndef __PEPPER_EVENT_TOPIC_H__
#define __PEPPER_EVENT_TOPIC_H__

#include <pepper/event/observer.hpp>

#include <pepper/vector.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace event {

  template <typename T> class topic
  {
    public:
      topic()   = default;
      ~topic()  = default;

    private:
      std::vector<std::shared_ptr<event::observer<T>>> _observers;

    public:
      topic<T> &connect(const std::shared_ptr<event::observer<T>> &observer)
      {
        _observers.emplace_back( observer );
        return *this;
      }

    public:
      void publish(const T &value) const
      {
        for (const auto &observer : _observers)
        {
          observer->notify( value );
        }
      }  
  };

} }

#endif // __PEPPER_EVENT_SUBJECT_H__
