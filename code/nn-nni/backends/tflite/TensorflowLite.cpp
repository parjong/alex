#include "nni/core/Engine.h"

#include <tensorflow/contrib/lite/model.h>
#include <tensorflow/contrib/lite/kernels/register.h>

#include <tensor/lexical_layout.h>

tensor::shape shape_of(const TfLiteTensor *tensor)
{
  tensor::shape res;

  const int rank = tensor->dims->size;

  res.resize(rank);
  for (int axis = 0; axis < rank; ++axis)
  {
    res.dim(axis) = tensor->dims->data[axis];
  }

  return res;
}

template<typename DType> class TfLiteTensorAccessor : public TensorAccessor<DType>
{
public:
  TfLiteTensorAccessor(const tensor::shape &shape, DType *data) : _shape{shape}, _data{data}
  {
    assert(data != nullptr);
  }

public:
  DType at(const tensor::index &index) const override
  {
    return _data[_layout.offset(_shape, index)];
  }

public:
  DType &at(const tensor::index &index) override
  {
    return _data[_layout.offset(_shape, index)];
  }

private:
  tensor::shape const _shape;
  DType * const _data;

private:
  const tensor::lexical_layout _layout;
};

struct TfLiteTensorState
{
  virtual ~TfLiteTensorState() = default;

  virtual uint32_t num_tensors(void) const = 0;

  virtual TfLiteTensor *object(uint32_t n) = 0;
  virtual const TfLiteTensor *object(uint32_t n) const = 0;
};

class TfLiteInputState final : public TfLiteTensorState
{
public:
  TfLiteInputState(tflite::Interpreter &interp) : _interp(interp)
  {
    // DO NOTHING
  }

public:
  uint32_t num_tensors(void) const override
  {
    return _interp.inputs().size();
  }

public:
  TfLiteTensor *object(uint32_t n) override
  {
    return _interp.tensor(_interp.inputs().at(n));
  }

  const TfLiteTensor *object(uint32_t n) const override
  {
    return _interp.tensor(_interp.inputs().at(n));
  }

private:
  ::tflite::Interpreter &_interp;
};

class TfLiteOutputState final : public TfLiteTensorState
{
public:
  TfLiteOutputState(tflite::Interpreter &interp) : _interp(interp)
  {
    // DO NOTHING
  }

public:
  uint32_t num_tensors(void) const override
  {
    return _interp.outputs().size();
  }

public:
  TfLiteTensor *object(uint32_t n) override
  {
    return _interp.tensor(_interp.outputs().at(n));
  }

  const TfLiteTensor *object(uint32_t n) const override
  {
    return _interp.tensor(_interp.outputs().at(n));
  }

private:
  ::tflite::Interpreter &_interp;
};

class TfLiteState : public State
{
public:
  TfLiteState(TfLiteTensorState *tensors) : _tensors(tensors)
  {
    // DO NOTHING
  }

public:
  uint32_t num_tensors(void) const override
  {
    return _tensors->num_tensors();
  }

public:
  std::string name(uint32_t n) const override
  {
    return _tensors->object(n)->name;
  }

public:
  tensor::shape shape(uint32_t n) const override
  {
    return shape_of(_tensors->object(n));
  }

public:
  TensorRef<float> as_float(uint32_t n) override
  {
    TfLiteTensor* tensor = _tensors->object(n);

    if (tensor->type == tflite::typeToTfLiteType<float>())
    {
      auto shape = shape_of(tensor);
      auto data = tensor->data.f;

      auto acc = std::make_unique<TfLiteTensorAccessor<float>>(shape, data);

      return TensorRef<float>{std::move(acc)};
    }

    return TensorRef<float>{nullptr};
  }

private:
  TfLiteTensorState *_tensors;
};

class TfLiteSession final : public Session
{
public:
  TfLiteSession(const std::string &path)
  {
    _model = tflite::FlatBufferModel::BuildFromFile(path.c_str());

    tflite::ops::builtin::BuiltinOpResolver resolver;
    tflite::InterpreterBuilder build{*_model, resolver};

    build(&_interp);
  }

public:
  bool prepare(const std::function<void (State &)> &f)
  {
    _interp->AllocateTensors();

    TfLiteInputState input_state(*_interp);
    TfLiteState state(&input_state);

    f(state);

    return true;
  }

  bool invoke(void)
  {
    return kTfLiteOk == _interp->Invoke();
  }

  bool teardown(const std::function<void (State &)> &f)
  {
    TfLiteOutputState output_state(*_interp);
    TfLiteState state(&output_state);

    f(state);

    return true;
  }

private:
  std::unique_ptr<tflite::FlatBufferModel> _model;
  std::unique_ptr<tflite::Interpreter> _interp;
};

std::unique_ptr<Session> make_session(const Arguments &args)
{
  return std::make_unique<TfLiteSession>(args.at(0));
}
