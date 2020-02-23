#ifndef __INSTR_H__
#define __INSTR_H__

#include "opcode.h"

// An "instruction"
struct Instr
{
  virtual ~Instr() = default;

  // SLOT
  virtual Opcode opcode(void) const = 0;
  
  // Visitor interface
};

#endif // __INSTR_H__
