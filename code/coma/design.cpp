// This enum enumerates all the possible algorithms available in coma
enum Algorithm // Algorithm? Policy? ...
{
  // No Reuse
  LinearBump,
  // Reuse
  LinearFirstFit,
};

// Each algorithm defines the "Problem" class that describes the exact problem that it aims to solve.
template <Algorithm Alg> class Problem;

// Each algorithm implements "solve" function, which takes a corresponding "Problem" instance.
// How to handle errors?
//
// There are two possible designs.
// 1. Use "return" value
// 2. Extend "problem" itself
//
// _coma_ takes the second approach. 
//
// Why?
// - Each allocation algorithm may have their own reasons of failures.
template <Algorithm Alg> void solve(Problem<Alg> *);

using ItemCount = uint32_t;
using ItemLabel = uint32_t;
using ItemOffset = uint32_t;

template <> class Problem<LinearBump>
{
public:
  virtual ~Problem() = default;

public: // Input

  // Returns the number of items.
  //
  // When count() return "N", it means that there are N items whose label is within [0, N)
  virtual uint32_t count(void) const = 0;

  // Return the size of item N
  virtual uint32_t size(const ItemLabel &) const = 0;

public: // Output
  
  virtual void locate(const ItemLabel &, const ItemOffset &) const = 0;
};

template <> void solve(Problem<LinearBump> &p)
{
  ItemOffset next = 0;

  for (uint32_t n = 0; n < p.count(); ++n)
  {
    // Reserve [next, next + size(n))
    p.locate(n, next);
    next += p.size(n);
  }
}

int main(int argc, char **argv)
{
  return 0;
}
