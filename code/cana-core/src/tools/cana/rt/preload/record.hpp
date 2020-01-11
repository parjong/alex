#ifndef __CANA_RT_PRELOAD_RECORD_H__
#define __CANA_RT_PRELOAD_RECORD_H__

#include "arg.hpp"
#include "env.hpp"

#include <boost/filesystem.hpp>
#include <string>

namespace cana { namespace rt { namespace preload {

  class record
  {
    private:
      boost::filesystem::path _image;
      preload::arg _arg;
      preload::env _env;

    public:
      record(const boost::filesystem::path &image, char **argv, char **envp);

    public:
      const std::string &image(void) const;

    public:
      const preload::arg &arg(void) const;
      const preload::env &env(void) const;
  };

} } }

#endif
