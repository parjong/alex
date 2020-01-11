#ifndef __TENSOR_LEXICAL_LAYOUT_H__
#define __TENSOR_LEXICAL_LAYOUT_H__

#include "tensor/layout.h"

namespace tensor
{

struct lexical_layout : public layout
{
  lexical_layout();

  static const lexical_layout &get(void);
};

} // namespace tensor

#endif // __TENSOR_LEXICAL_LAYOUT_H__
