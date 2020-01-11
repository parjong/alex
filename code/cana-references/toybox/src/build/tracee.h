#ifndef TRACEE_H__
#define TRACEE_H__

class Tracee
{
  public:
    Tracee();
    virtual ~Tracee();
  public:
    virtual void run(void) = 0;
};

class ExecTracee : public Tracee
{
  public:
    ExecTracee(const char *path, char * const *argv, char * const *envp);
    virtual ~ExecTracee();
  private:
    const char *path_;
    char * const *argv_;
    char * const *envp_;
  public:
    virtual void run(void);
};

#endif
