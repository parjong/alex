#include <string>
#include <vector>

#define CPU_ONLY
#include <caffe/caffe.hpp>
#undef CPU_ONLY

struct Model
{
  uint32_t _id;
};

struct EnsembledModel
{
  std::vector<Model> models;

  // Ensemble Algorithm?
};

struct CaffeModel
{
  std::string prototxt;
  std::string caffemodel;
};

//
// infer
// update
//
#include <vector>
#include <string>

int main(int argc, char **argv)
{
  google::InitGoogleLogging(argv[0]);

  std::vector<std::string> stages;
  caffe::Net<float> net(argv[1], caffe::TEST, 0 /* level */, &stages);

  std::cout << "# of stages: " << stages.size() << std::endl;

  for (const auto &stage : stages)
  {
    std::cout << stage << std::endl;
  }

  net.CopyTrainedLayersFrom(argv[2]);

  float loss = 0.0;

  const auto &result = net.Forward(&loss);

  std::cout << "loss: " << loss << std::endl;

  return 0;
}
