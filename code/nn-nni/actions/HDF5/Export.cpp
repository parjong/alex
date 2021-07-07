#include "nni/core/ActionEntry.h"

#include <tensor/lexical_layout.h>
#include <tensor/enumerator.h>

#include <H5Cpp.h>

#include <cassert>

uint32_t num_elements(const tensor::shape &shape)
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

class HDF5ExportAction final : public Action
{
public:
  HDF5ExportAction(const std::string &path) : _path{path}
  {
    // DO NOTHING
  }

public:
  void run(State &s) override;

private:
  const std::string _path;
};

void HDF5ExportAction::run(State &s)
{
  H5::H5File file{_path, H5F_ACC_TRUNC};

  for (uint32_t n = 0; n < s.num_tensors(); ++n)
  {
    const auto &shape = s.shape(n);

    const uint32_t rank = shape.rank();

    hsize_t dims[rank] = { 0 };

    for (uint32_t axis = 0; axis < rank; ++axis)
    {
      dims[axis] = shape.dim(axis);
    }

    // TODO Support non-float tensors
    auto tensor = s.as_float(n);

    H5::DataSpace dataspace{static_cast<int>(rank), dims};
    H5::DataSet dataset = file.createDataSet(s.name(n), H5::PredType::IEEE_F32BE, dataspace);

    std::vector<float> raw;

    const tensor::lexical_layout l;
    raw.resize(num_elements(shape));

    for (tensor::enumerator e{shape}; e.valid(); e.next())
    {
      raw[l.offset(shape, e.curr())] = tensor.at(e.curr());
    }

    dataset.write(raw.data(), H5::PredType::NATIVE_FLOAT);
  }
}

std::unique_ptr<Action> make_action(const Arguments &args)
{
  return std::make_unique<HDF5ExportAction>(args.at(0));
}
