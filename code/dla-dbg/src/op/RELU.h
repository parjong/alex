#ifndef __OP_RELU_H__
#define __OP_RELU_H__

#include "core/instr.h"

struct Relu final : public Instr
{
  Opcode opcode(void) const final { return Opcode::RELU; }
  // COMPUTE
  // - ZERO_POINT
  //
  // SRC ADDR (DLA Buffer)
  // - OFFSET, MOD_Y, MOD_Z
  //
  // DST ADDR (DLA Buffer)
  // - OFFSET, MOD_Y, MOD_Z
};

#endif // __OP_RELU_H__
