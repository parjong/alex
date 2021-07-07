#ifndef __UNIQUE_H__
#define __UNIQUE_H__

#include <vector>
#include <memory>

namespace unique {
  template <typename T> struct vector : public std::vector<std::unique_ptr<T>> {
    vector() = default;
    virtual ~vector() = default;
  };
}

#endif
