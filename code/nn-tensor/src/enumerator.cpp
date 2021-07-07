#include "tensor/enumerator.h"

#include <cassert>

namespace tensor
{

enumerator::enumerator(const shape &s) : _shape{s}
{
  _index.resize(_shape.rank());

  for (uint32_t axis = 0; axis < _shape.rank(); ++axis)
  {
    _index.at(axis) = 0;
  }

  for (_cursor = 0; _cursor < _shape.rank(); ++_cursor)
  {
    if (_index.at(_cursor) < _shape.dim(_cursor))
    {
      break;
    }
  }
}

bool enumerator::valid(void) const
{
  assert(_index.rank() == _shape.rank());
  return _cursor < _shape.rank();
}

enumerator &enumerator::next(void)
{
  const auto rank = _shape.rank();

  // Find axis to be updated
  while((_cursor < rank) && !(_index.at(_cursor) + 1 < _shape.dim(_cursor)))
  {
    ++_cursor;
  }

  if(_cursor < rank)
  {
    // Update index
    _index.at(_cursor) += 1;

    for (uint32_t axis = 0; axis < _cursor; ++axis)
    {
      _index.at(axis) = 0;
    }

    // Update cursor
    _cursor = 0;
  }

  return (*this);
}

} // namespace tensor
