#include <caffe/proto/caffe.pb.h>

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <cleo/Runner.h>
#include <cleo/AtomApp.h>
#include <cleo/SelectorApp.h>
#include <cleo/HelpSupport.h>

#include <map>
#include <set>
#include <string>

#include <iostream>

// TODO Implement "test"
struct DecodeApp final : public cleo::AtomApp
{
  int run(const cleo::Args *) const final;
};

int DecodeApp::run(const cleo::Args *) const
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

struct EncodeApp final : public cleo::AtomApp
{
  int run(const cleo::Args *) const final;
};

int EncodeApp::run(const cleo::Args *) const
{
  caffe::NetParameter net;

  google::protobuf::io::IstreamInputStream iis{&std::cin};

  if (!google::protobuf::TextFormat::Parse(&iis, &net))
  {
    // TODO Show error message
    return -1;
  }

  if (!net.SerializeToOstream(&std::cout))
  {
    // TODO Show error message
    return -1;
  }

  return 0;
}

int main(int argc, char **argv)
{
  cleo::SelectorApp app;

  app.command("decode").entry<DecodeApp>();
  app.command("encode").entry<EncodeApp>();
  app.command("help").entry<cleo::HelpCommand>();

  return cleo::run(app).as("caffekit").with(argc, argv);
}
