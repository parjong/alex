#ifndef COMMAND_H__
#define COMMAND_H__

#include "context.h"
#include "hiberlite.h"

#include <string>
#include <vector>

class Command
{
	friend class hiberlite::access;
	template<class Ar> void hibernate(Ar & ar)
	{
		ar & HIBERLITE_NVP(cwd_);
		ar & HIBERLITE_NVP(exe_);
    ar & HIBERLITE_NVP(arg_);
    ar & HIBERLITE_NVP(env_);
		ar & HIBERLITE_NVP(tStart_);
		ar & HIBERLITE_NVP(tFinish_);
	}
  public:
    Command();
    Command(const SyscallContext& ctxt, const char *path, const char **arg, const char **env);
  public:
    ~Command();
  
  private:
    std::string cwd_;
    std::string exe_;
    std::vector<std::string> arg_;
    std::vector<std::string> env_;
  public:
    const std::string& cwd(void) const;
    const std::string& exe(void) const;
    const std::vector<std::string>& arg(void) const;
    const std::vector<std::string>& env(void) const;

  public:
    void update(const SyscallContext& ctxt, const char *path, const char **arg, const char **env);

  private:
    long tStart_;
  public:
    void setStart(void);
    long getStart(void) const;

  private:
    long tFinish_;
  public:
    void setFinish(void);
    long getFinish(void) const;
};

class CompileCommand
{
  public:
    CompileCommand();
    ~CompileCommand();
};

#endif
