#include "terminator.h"

#include <stdlib.h>
#include <signal.h>

Terminator::Terminator()  { }
Terminator::~Terminator() { }

ExitedTerminator::ExitedTerminator(int code) : code_(code)  { } 
ExitedTerminator::~ExitedTerminator() { }

void ExitedTerminator::terminate(void) const 
{
  exit(code_);
}

SignaledTerminator::SignaledTerminator(int sig) : sig_(sig) { }
SignaledTerminator::~SignaledTerminator() { }

void SignaledTerminator::terminate(void) const
{
  raise(sig_);
  exit(0);
}
