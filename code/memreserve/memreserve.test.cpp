#include <gtest/gtest.h>

#include <cassert>

namespace
{

// Record avaiable memory partitions
struct MemoryMap
{
  MemoryMap(uint32_t len = 0xffffffff)
  {
    // Region [0, max) is avaiable at the beginning
    _content[len] = len;
  }

  // Let's exclude [s, e) from the avaiable region
  void exclude(uint32_t s, uint32_t e)
  {
    assert(s <= e);

    if (s == e)
    {
      // Nothing to do
      return;
    }

    // lower_bound() returns an iterator to the first element not less than the given key
    auto lb = _content.lower_bound(s);

    // TODO Check invariant!
    // [prev_s, prev_e) [curr_s, curr_e) [next_s, next_e)

    auto curr_s = lb->first - lb->second;
    auto curr_e = lb->first;

    // "lower_bound" above ensures that "prev_s < s <= curr_e"

    if (curr_s < s)
    {
      _content[s] = s - curr_s;
      // [prev_s, prev_e) [curr_s, s) [curr_s, curr_e) [next_s, next_s)
    }

    // Two possible states at this point
    //
    // STATE 1.
    //
    // [prev_s, prev_e) [curr_s, s) [curr_s, curr_e) [next_s, next_s)
    //
    // STATE 2.
    //                 s
    // [prev_s, prev_e) [curr_s, curr_e) [next_s, next_s)

    if (e < curr_e)
    {
      // [prev_s, prev_e) [curr_s, s) [e, curr_e) [next_s, next_s)
      // OR
      // [prev_s, prev_e) [e, curr_e) [next_s, next_e)
      _content[curr_e] = curr_e - e; // 0xffffffff - 5
    }
    else
    {
      // e >= curr_e
      // [prev_s, prev_e) [curr_s, s) [next_s, next_s)
      // [prev_s, prev_e) [next_s, next_e)
      _content.erase(curr_e);
      exclude(curr_e, e);
    }
  }

  int64_t firstfit(uint32_t len) const
  {
    for (auto it = _content.begin(); it != _content.end(); ++it)
    {
      if (it->second >= len)
      {
        return it->first - it->second;
      }
    }

    return -1; // INFEASIBLE
   }

  std::map<uint32_t /* END */, uint32_t /* LEN */ > _content;

  void print(void) const
  {
    for (const auto &pair : _content)
    {
      auto slot_s = pair.first - pair.second;
      auto slot_e = pair.first;
      std::cout << "[" << slot_s << " - " << slot_e << ") ";
    }
    std::cout << std::endl;
  }
};

} // namespace

TEST(MemoryReserveMap, test)
{
  MemoryMap mmap{64};

  std::cout << "INITIAL" << std::endl;
  mmap.print();

  auto exclude = [&] (uint32_t s, uint32_t e)
  {
    mmap.exclude(s, e);
    std::cout << "exclude [" << s << "," << e << ")" << std::endl;
    mmap.print();
  };

  exclude(3, 5);
  exclude(4, 5);
  exclude(9, 16);
  exclude(17, 18);
  exclude(6, 19);

  SUCCEED();
}

TEST(MemoryReserveMap, firstfit)
{
  MemoryMap mm{64};

  mm.exclude(2, 5);
  mm.exclude(9, 16);
  mm.print();

  auto firstfit = [&] (uint32_t l)
  {
    std::cout << "firstfit(" << l << ") is " << mm.firstfit(l) << std::endl;
  };

  firstfit(2);
  firstfit(4);
  firstfit(8);

  SUCCEED();
}
