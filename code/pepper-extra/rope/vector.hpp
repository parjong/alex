#ifndef __PEPPER_ROPE_VECTOR_H__
#define __PEPPER_ROPE_VECTOR_H__

#include <vector>
#include <functional>

namespace pepper { namespace rope {
  
  template <typename T> class vector
  {
    private:
      const std::vector<T> &_first;
      const std::vector<T> &_second;

    public:
      vector(const std::vector<T> &first, const std::vector<T> &second)
        : _first(first), _second(second)
      {
        // DO NOTHING
      }
      ~vector() = default;

    public:
      void iter(std::function<void (const T &)> fn)
      {
        for (const auto &elem : _first) 
          fn(elem);
        for (const auto &elem : _second) 
          fn(elem);
      }
  };

  template <typename T> vector<T> make(const std::vector<T> &first, const std::vector<T> &second)
  {
    return vector<T>{ first, second };
  }

} } 

#endif
