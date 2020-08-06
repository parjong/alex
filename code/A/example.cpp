#include <iostream>

enum class Version
{
  v200,
  v201
};

int main(int argc, char **argv)
{
  Version v = Version:: DEFAULT_VERSION;

  switch (v)
   {
     case Version::v200:
       std::cout << "v200" << std::endl;
       break;
     case Version::v201:
       std::cout << "v201" << std::endl;
       break;
     default:
       std::cout << "UNKNOWN" << std::endl;
       break;
   }

  return 0;
}
