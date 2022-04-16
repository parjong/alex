#ifndef __NAMED_H__
#define __NAMED_H__

#include <map>
#include <string>
#include <memory>

namespace pepper {
  /** Name Object Pool */
  template <typename T> class named {
    public:
      named() = default;
      virtual ~named() = default;

    private:
      std::map<std::string, std::unique_ptr<T>> objects_;

    public:
      void enroll(const std::string &name, T *object) {
        objects_[name] = std::unique_ptr<T>(object);
      }
      
      T *lookup(const std::string &name) const {
        auto it = objects_.find(name);

        if ( it != objects_.end() ) {
          return it->second.get();
        }

        return nullptr;
      }
  };
}

#endif
