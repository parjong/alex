#include <caffe/proto/caffe.pb.h>

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <map>
#include <string>

#include <iostream>

// TODO Implement "test"
int decode(int, const char * const *)
{
  caffe::NetParameter net;

  // Parse "binary" model from standard input
  if (!net.ParseFromIstream(&std::cin))
  {
    // TODO Show error message
    return -1;
  }

  google::protobuf::io::OstreamOutputStream oos{&std::cout};

  if (google::protobuf::TextFormat::Print(net, &oos))
  {
    // TODO Show error message
    return -1;
  }

  return 0;
}

int main(int argc, char **argv)
{
  std::map<std::string, int (*)(int, const char * const *)> commands;

  commands["decode"] = decode;
  // TODO Implement 'encode'

  if (argc < 2)
  {
    // TODO Show help message
    std::cerr << "ERROR: No command found" << std::endl;
    return -1;
  }

  std::string command{argv[1]};

  // TODO Check whether 'command' is valid or not
  auto func = commands.at(command);
  return func(0, nullptr);;
}
