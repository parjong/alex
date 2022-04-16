#ifndef COMMAND_RUNNER_H__
#define COMMAND_RUNNER_H__

#include <string>
#include <vector>

class CommandRunner
{
  public:
    CommandRunner();
    virtual ~CommandRunner();
  public:
    virtual void run(const std::string& cwd, const std::string& exec, const std::vector<std::string>& arg, const std::vector<std::string>& env) = 0;
};

class ExecCommandRunner : public CommandRunner
{
  public:
    ExecCommandRunner();
    virtual ~ExecCommandRunner();
  public:
    virtual void run(const std::string& cwd, const std::string& exec, const std::vector<std::string>& arg, const std::vector<std::string>& env);
};

class ForkCommandRunner : public CommandRunner
{
  public:
    ForkCommandRunner();
    virtual ~ForkCommandRunner();
  private:
    FILE *rdout_;  
  public:
    void redirectOutput(FILE *out);
  public:
    virtual void run(const std::string& cwd, const std::string& exec, const std::vector<std::string>& arg, const std::vector<std::string>& env);
};

#endif
