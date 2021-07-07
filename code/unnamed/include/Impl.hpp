// TODO Update ifdef guard
#ifndef __A__
#define __A__

#include <cstdint>

class LiveIntervalSet
{
  // TODO
  //  Parameterize "address space" type
public:
  // [0, len) is live at the beginning
  LiveIntervalSet(uint32_t len = 0xffffffff)
  {
    _content[len] = len;
  }

public:
  // DESIGN
  //
  // To mark [s, e) as dead (where e >= s)
  //
  //  mark_as_dead(start_offset(s), end_offset(e))
  //  mark_as_dead(start_offset(s), len(e - s)));
  //  notify(dead(start_offset(s), end_offset(e)));

public:
  // Walk over live intervals

public:
  // Find the fit
  //
  // find(firstfist(len(l)));
  //
  // Q. Is it possible to introduce extensible search algorithm???
private:
  std::map<uint32_t /* END */, uint32_t /* LEN */> _content;
};

#endif // __A__
