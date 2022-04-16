#include <nni/core/Engine.h>

#include <caffe/caffe.hpp>

#include <cassert>

template<typename DType> tensor::shape shape_of(const caffe::Blob<DType> *blob)
{
  assert(blob != nullptr);

  const int rank = blob->num_axes();

  tensor::shape res;

  res.resize(rank);
  for (int axe = 0; axe < rank; ++axe)
  {
    res.dim(axe) = blob->shape(axe);
  }

  return res;
}

#include <tensor/lexical_layout.h>

template<typename DType> class CaffeTensorAccessor : public TensorAccessor<DType>
{
public:
  CaffeTensorAccessor(const tensor::shape &shape, DType *data) : _shape{shape}, _data{data}
  {
    // DO NOTING
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

template<typename DType> struct CaffeBlobState
{
  virtual ~CaffeBlobState() = default;

  virtual uint32_t num_blobs(void) const = 0;

  virtual std::string name(uint32_t n) const = 0;
  virtual caffe::Blob<DType> *object(uint32_t n) = 0;
  virtual const caffe::Blob<DType> *object(uint32_t n) const = 0;
};

template<typename DType>
class CaffeInputState final : public CaffeBlobState<DType>
{
public:
  CaffeInputState(caffe::Net<DType> &net) : _net(net)
  {
    // DO NOTHING
  }

public:
  uint32_t num_blobs(void) const override { return _net.num_inputs(); }

public:
  std::string name(uint32_t n) const override
  {
    return _net.blob_names().at(_net.input_blob_indices().at(n));
  }

  caffe::Blob<DType> *object(uint32_t n) override
  {
    return _net.input_blobs().at(n);
  }

  const caffe::Blob<DType> *object(uint32_t n) const override
  {
    return _net.input_blobs().at(n);
  }

private:
  caffe::Net<DType> &_net;
};

template<typename DType>
class CaffeOutputState final : public CaffeBlobState<DType>
{
public:
  CaffeOutputState(caffe::Net<DType> &net) : _net(net)
  {
    // DO NOTHING
  }

public:
  uint32_t num_blobs(void) const override { return _net.num_outputs(); }

public:
  std::string name(uint32_t n) const override
  {
    return _net.blob_names().at(_net.output_blob_indices().at(n));
  }

  caffe::Blob<DType> *object(uint32_t n) override
  {
    return _net.output_blobs().at(n);
  }

  const caffe::Blob<DType> *object(uint32_t n) const override
  {
    return _net.output_blobs().at(n);
  }

private:
  caffe::Net<DType> &_net;
};

template<typename DType> class CaffeState;

template<> class CaffeState<float> : public State
{
public:
  CaffeState(CaffeBlobState<float> &blobs) : _blobs(blobs)
  {
    // DO NOTHING
  }

public:
  uint32_t num_tensors(void) const override
  {
    return _blobs.num_blobs();
  }

public:
  std::string name(uint32_t n) const override
  {
    return _blobs.name(n);
  }

public:
  tensor::shape shape(uint32_t n) const override
  {
    return shape_of(_blobs.object(n));
  }

public:
  TensorRef<float> as_float(uint32_t n) override
  {
    auto blob = _blobs.object(n);

    auto shape = shape_of(blob);
    auto data = blob->mutable_cpu_data();

    auto acc = std::make_unique<CaffeTensorAccessor<float>>(shape, data);

    return TensorRef<float>{std::move(acc)};
  }

private:
  CaffeBlobState<float> &_blobs;
};

template<typename DType> class CaffeSession final : public Session
{
public:
  CaffeSession(const std::string &path) : _net{path, caffe::TEST}
  {
    // DO NOTHING
  }

public:
  bool prepare(const std::function<void (State &)> &f)
  {
    CaffeInputState<DType> input_state(_net);
    CaffeState<DType> state(input_state);

    f(state);

    return true;
  }

  bool invoke(void)
  {
    _net.Forward();
    return true;
  }

  bool teardown(const std::function<void (State &)> &f)
  {
    CaffeOutputState<DType> output_state(_net);
    CaffeState<DType> state(output_state);

    f(state);

    return true;
  }

private:
  caffe::Net<DType> _net;
};

#include <mutex>

static std::once_flag glog_init_flag;

void glog_init(void)
{
  google::InitGoogleLogging("nni");
}

std::unique_ptr<Session> make_session(const Arguments &args)
{
  std::call_once(glog_init_flag, glog_init);
  return std::make_unique<CaffeSession<float>>(args.at(0));
}
