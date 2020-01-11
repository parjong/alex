#include "loader.hpp"

#include <memory>

extern "C" std::unique_ptr<cana::ext::loader> make(void)
{
  return std::unique_ptr<cana::ext::loader>{new cana::binder::native::loader()};
}
