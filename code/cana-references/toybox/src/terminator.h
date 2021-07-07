#ifndef TERMINATOR_H__
#define TERMINATOR_H__

class Terminator
{
  public:
    Terminator();
    virtual ~Terminator();
  public:
    virtual void terminate(void) const = 0;
};

class ExitedTerminator : public Terminator
{
  public:
    ExitedTerminator(int code);
    virtual ~ExitedTerminator();
  private:
    int code_;
  public:
    virtual void terminate(void) const;
};

class SignaledTerminator : public Terminator
{
  public:
    SignaledTerminator(int sig);
    virtual ~SignaledTerminator();
  private:
    int sig_;
  public:
    virtual void terminate(void) const;
};

#endif
