#include "nni/core/ActionEntry.h"

#include <tensor/lexical_layout.h>
#include <tensor/enumerator.h>

#include <H5Cpp.h>

#include <cassert>

static uint32_t num_elements(const tensor::shape &shape)
{
  const auto rank = shape.rank();

  if (rank == 0)
  {
    return 0;
  }

  uint32_t res = 1;

  for (uint32_t axis = 0; axis < rank; ++axis)
  {
    res *= shape.dim(axis);
  }

  return res;
}

class HDF5ImportAction final : public Action
{
public:
  HDF5ImportAction(const std::string &path) : _path{path}
  {
    // DO NOTHING
  }

public:
  void run(State &s) override;

private:
  const std::string _path;
};

void HDF5ImportAction::run(State &s)
{
  H5::H5File file{_path, H5F_ACC_RDONLY};

  for (uint32_t n = 0; n < s.num_tensors(); ++n)
  {
    const auto name = s.name(n);
    const auto &shape = s.shape(n);

    try
    {
      auto dataset = file.openDataSet(name);

      // TODO Support non-float tensors
      assert(dataset.getDataType() == H5::PredType::IEEE_F32BE);

      auto tensor = s.as_float(n);

      std::vector<float> raw;

      // TODO Check shape consistency
      const tensor::lexical_layout l;
      raw.resize(num_elements(shape));

      // Read data from HDF5 file
      dataset.read(raw.data(), H5::PredType::NATIVE_FLOAT);

      // Transfer
      for (tensor::enumerator e{shape}; e.valid(); e.next())
      {
        tensor.at(e.curr()) = raw[l.offset(shape, e.curr())];
      }
    }
    catch (const H5::FileIException &e)
    {
      // DO NOTHING
    }
  }
}

std::unique_ptr<Action> make_action(const Arguments &args)
{
  return std::make_unique<HDF5ImportAction>(args.at(0));
}
