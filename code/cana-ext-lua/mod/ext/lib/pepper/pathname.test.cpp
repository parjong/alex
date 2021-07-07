#include <pepper/testing.hpp>
#include <pepper/pathname.hpp>

COLLECTION(pathname)
{
  struct root : public pepper::pathname::dir
  {
    root(const std::string &path) : dir{ path }
    {
      // DO NOTHING
    }

    virtual ~root() = default;
  };

  FACT(derived_dir)
  {
    ::root r{ "/" };
  }
}
