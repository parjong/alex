#include <cana/ext/app.hpp>
#include <cana/ext/service.hpp>
#include <cana/proc/info.hpp>

#include <boost/filesystem.hpp>

#include <memory>
#include <cstdio>

namespace {

  class app : public cana::ext::app
  {
    private:
      boost::filesystem::path _out;

    public:
      app(const cana::ext::service &s)
      {
        _out = s.storage()->resolve("echo.txt");
      }

    public:
      virtual void notifyProcessEnter(const cana::proc::info &pi)
      {
        // DO NOTHING
      }

      virtual void notifyProcessLeave(const cana::proc::info &pi)
      {
        FILE *fp = fopen(_out.c_str(), "a+");
        fprintf(fp, "image = %s\n", pi.image().c_str());

        int argcnt = 0;

        auto argfn = [&] (const std::string &arg)
        {
          fprintf(fp, "arg %d = %s\n", argcnt++, arg.c_str());
        };

        pi.arg().each(argfn);

        auto envfn = [&] (const std::string &k, const std::string &v)
        {
          fprintf(fp, "env '%s' = '%s'\n", k.c_str(), v.c_str());
        };

        pi.env().each(envfn);

        fclose(fp);
      }
  };

}

extern "C" std::unique_ptr<cana::ext::app> make(const cana::ext::service &s)
{
  return std::unique_ptr<cana::ext::app>{ new ::app(s) };
}
