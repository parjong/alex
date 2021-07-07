#include "nni/core/ActionEntry.h"

#include <iostream>

std::ostream &operator<<(std::ostream &os, const tensor::shape &shape)
{
  if (shape.rank() > 0)
  {
    os << shape.dim(0);

    for (uint32_t axis = 1; axis < shape.rank(); ++axis)
    {
      os << "," << shape.dim(axis);
    }
  }
  return os;
}

struct ShowAction final : public Action
{
  void run(State &s) override
  {
    for (uint32_t n = 0; n < s.num_tensors(); ++n)
    {
      std::cout << "Tensor #" << n << ": " << s.name(n) << std::endl;
      std::cout << "  Shape: " << s.shape(n) << std::endl;
    }
  }
};

std::unique_ptr<Action> make_action(const Arguments &args)
{
  return std::make_unique<ShowAction>();
}
