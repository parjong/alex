#include <iostream>
#include <map>
#include <string>
#include <vector>

// Infrastructure
struct Op
{
  const char *opcode;
};

// Declaration
Op oplist[] = {
  { "RELU" },
  // END
  { nullptr },
};

// Consumers
int gen_include_all_header(void)
{
  Op *cursor = &oplist[0];

  for (Op *curosr = &oplist[0]; cursor->opcode != nullptr; cursor += 1)
  {
    std::cout << "#include \"op/" << cursor->opcode << ".h\"" << std::endl;
  }

  return 0;
}

int gen_opcode_header(void)
{
  std::cout << "#ifndef __OPCODE_H__" << std::endl;
  std::cout << "#define __OPCODE_H__" << std::endl;
  std::cout << std::endl;
  std::cout << "enum class Opcode" << std::endl;
  std::cout << "{" << std::endl;

  // Fill in the content
  Op *cursor = &oplist[0];

  for (Op *curosr = &oplist[0]; cursor->opcode != nullptr; cursor += 1)
  {
    std::cout << "  " << cursor->opcode << "," << std::endl;
  }

  std::cout << "};" << std::endl;
  std::cout << std::endl;
  std::cout << "#endif // __OPCODE_H__" << std::endl;

  return 0;
}

int entry(const std::vector<std::string> &args)
{
  std::map<std::string, int (*)(void)> fns;

  fns["--gen-include-all-header"] = gen_include_all_header;
  fns["--gen-opcode-header"] = gen_opcode_header;

  auto fn = fns.at(args.at(0));

  return fn();
}

int main(int argc, char **argv)
{
  std::vector<std::string> args;

  for (uint32_t n = 1; n < argc; ++n)
  {
    args.emplace_back(argv[n]);
  }

  return entry(args);
}
