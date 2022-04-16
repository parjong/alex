#include "plugin/actor/gcc.h"

#include <vector>

namespace gcc
{
  class arg
  {
    public:
      arg() { }
      virtual ~arg() { }
  };

  class unknown : public arg
  {
    public:
      unknown(const std::string& val) 
        : val_(val)
      { }
      virtual ~unknown() { }
    private:
      std::string val_;
  };
  
  class source : public arg
  {
    public:
      source(const std::string& src)
        : src_(src)
      { }
      virtual ~source() { }
    private:
      std::string src_;
  };

  class args
  {
    public:
      args() { }
    public:
      ~args()
      {
        for (arg *ptr : args_)        
          delete ptr;        
      }
    private:    
      std::vector<arg *> args_;
  };
}

gcc_actor::gcc_actor() { }
gcc_actor::~gcc_actor() { }      
    
void gcc_actor::perform(const abstract_system& p,
                        const std::string& wd, 
                        const std::string& path, 
                        const arg_data& arg,
                        const env_data& env) const
{     
  std::vector<std::string> sources;

  std::vector<std::string> opts = arg.tl();

  for (const std::string& opt : opts)
  {
    if ( opt[0] != '-' )
      sources.push_back(opt);    
  }   

  for (const std::string& src : sources)
  {
    arg_data pp_arg;

    pp_arg.push_back(path);
    pp_arg.push_back("-E");
    pp_arg.push_back("-o");
    pp_arg.push_back(src + ".i");
    pp_arg.push_back(src);

    p.run(path, pp_arg, env);
  }
}

