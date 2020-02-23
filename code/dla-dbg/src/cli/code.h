#ifndef __CODE_H__
#define __CODE_H__

#include "core/instr.h"

#include <memory>
#include <vector>

// Code is a ordered sequence of instructions
class Code final
{
public:
  uint32_t size(void) const { return _instrs.size(); }

public:
  const Instr *at(uint32_t n) const { return _instrs.at(n).get(); }

public:
  Code *append(std::unique_ptr<Instr> &&ins)
  {
    _instrs.emplace_back(std::move(ins));
  }

private:
  std::vector<std::unique_ptr<Instr>> _instrs;
};

// A "Program" consists of Meta / Code / Data sections
struct Program
{
public: // Meta Section
  uint32_t const_segment_size;
  std::vector<uint32_t> host_segment_sizes;
  uint32_t dla_segment_size;
  // TODO Add "dsp_segment_size"
  // TODO Add "shared_segment_size"

  // _inputs.at(N) returns the index of the segment that (N + 1)-th input resides in
  std::vector<SegmentIndex> _inputs;
  std::vector<SegmentIndex> _outputs;

public: // Code Section
  Code _code;

public: // Data Section
  // Span<byte> _data;
};

#endif // __CODE_H__
