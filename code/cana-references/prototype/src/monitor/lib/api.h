#ifndef BC_API_H__
#define BC_API_H__

class execve_api
{
  public:
    execve_api();
  private:
    typedef int (*func_t)(const char *filename, char * const argv[], char * const envp[]);
    func_t func_;
  public:
    bool hook(void);
  public:
    int invoke(const char *filename, char * const argv[], char * const envp[]);
};    

extern execve_api _execve_api;

#endif
