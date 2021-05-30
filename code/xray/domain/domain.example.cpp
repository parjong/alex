#include "domain.example.h"

MyDomain *MyDomain::get(void)
{
  static MyDomain d;
  return &d;
}
