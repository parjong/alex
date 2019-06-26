#include <nnvm/node.h>
#include <nnvm/symbolic.h>
#include <nnvm/graph.h>
#include <nnvm/pass.h>
#include <nnvm/c_api.h>

#include <tvm/tvm.h>
#include <tvm/build_module.h>
#include <tvm/codegen.h>

//#include <base/Debug.h>

#include <dlpack/dlpack.h>

#include <iostream>
#include <vector>

namespace
{
nnvm::Graph *Apply(GraphHandle g, const std::string &name)
{
  GraphHandle ret;
  const char *passes[] = { name.c_str() };
  NNGraphApplyPasses(g, 1, passes, &ret);
  return reinterpret_cast<nnvm::Graph *>(ret);
}

void PrintJsonAttr(nnvm::Graph *g, const std::string &key)
{
  const char *json_out;
  int code_out;
  NNGraphGetJSONAttr(g, key.c_str(), &json_out, &code_out);
  std::cout << json_out << std::endl;
}

} // namespace

int main(int argc, char **argv)
{
  auto ifm = nnvm::Symbol::CreateVariable("ifm");
  ifm.SetAttrs({{"shape", "(1, 1, 4, 4)"}});
  ifm.Print(std::cout);

  auto ker = nnvm::Symbol::CreateVariable("ker");
  ker.SetAttrs({{"shape", "(1, 1, 1, 1)"}});

  auto bias = nnvm::Symbol::CreateVariable("bias");
  bias.SetAttrs({{"shape", "(1)"}});

  std::vector<const nnvm::Symbol *> conv2d_args{&ifm, &ker, &bias};
  auto conv2d = nnvm::Symbol::CreateFunctor(nnvm::Op::Get("conv2d"),
  {
    { "channels", "1" },
    { "kernel_size", "(1, 1)" },
  });
  conv2d.Compose(conv2d_args, { }, "conv2d");
  conv2d.Print(std::cout);

  // Q. How to build a Graph?
  // A. Check "NNGraphCreate" API implementation
  nnvm::Graph *g = nullptr;

  // Create a Graph
  g = new nnvm::Graph;

  g->outputs = conv2d.outputs;

  //
  // Infer Shape
  //
#if 0
  g = Apply(g, "InferShape");

  std::cout << "Begin Keys" << std::endl;
  for (const auto &attr : g->attrs)
  {
    std::cout << "'" << attr.first << "'" << std::endl;
  }
  std::cout << "End Keys" << std::endl;

  std::cout << "Let's check shape" << std::endl;
  PrintJsonAttr(g, "shape");

  std::cout << "Let's check shape_num_unknown_nodes" << std::endl;
  PrintJsonAttr(g, "shape_num_unknown_nodes");

  //
  // Print Graph
  //
  std::cout << "Let Print Graph IR" << std::endl;;

  g = Apply(g, "PrintGraphIR");
  PrintJsonAttr(g, "graphir");

  //
  // Save JSON
  //
  g = Apply(g, "SaveJSON");
  PrintJsonAttr(g, "json");
#endif

  g = Apply(g, "GraphCompile");

  //PrintJsonAttr(Apply(g, "PrintGraphIR"), "graphir");
  //PrintJsonAttr(Apply(g, "SaveJSON"), "json");

  std::cout << "Run TVM example" << std::endl;

  auto n = tvm::var("n");
  tvm::Array<tvm::Expr> shape{n};

  auto A = tvm::placeholder(shape, tvm::Float(32), "A");
  auto B = tvm::placeholder(shape, tvm::Float(32), "A");

  // C : tvm::Tensor
  auto C = tvm::compute(shape, [&A, &B] (tvm::Expr i) {
      return A[i] + B[i];
  }, "C");

  // s : tvm::Schedule
  auto s = tvm::create_schedule({ C->op });

#if 0
 	auto cAxis = C->op.as<tvm::ComputeOpNode>()->axis;

  tvm::IterVar bx, tx;
  s[C].split(cAxis[0], 64, &bx, &tx);
#endif

  auto args = tvm::Array<tvm::Tensor>({ A, B, C });
  std::unordered_map<tvm::Tensor, tvm::Buffer> binds;

  auto config = tvm::build_config();
  auto target = tvm::target::llvm();

  // lowered : tvm::Array<tvm::LoweredFunc>
  auto lowered = tvm::lower(s, args, "func", binds, config);

  std::cout << ">> LOWERED FUNC " << std::endl;
  std::cout << lowered[0]->body << std::endl;

  // module : tvm::runime::Module
  auto module = tvm::build(lowered, target, tvm::Target(), config);

  std::cout << ">> COMPILED FUNC " << std::endl;
  std::cout << module->GetSource() << std::endl;

  auto func = module->GetFunction("func", nullptr);

  float arr_A[16];
  float arr_B[16];
  float arr_C[16];

  for (uint32_t n = 0; n < 16; ++n)
  {
    arr_A[n] = n;
    arr_B[n] = n + 16;
    arr_C[n] = 0.0f;
  }

  DLContext dl_context;

  dl_context.device_type = kDLCPU;
  dl_context.device_id = 0;

  DLDataType dl_f32;

  dl_f32.code = kDLFloat;
  dl_f32.bits = 32;
  dl_f32.lanes = 1;

  int64_t dims[] = { 16 };

  DLTensor tensor_A;
  tensor_A.data = arr_A;
  tensor_A.ctx = dl_context;
  tensor_A.dtype = dl_f32;
  tensor_A.ndim = 1;
  tensor_A.shape = dims;
  tensor_A.strides = nullptr;
  tensor_A.byte_offset = 0;

  DLTensor tensor_B;
  tensor_B.data = arr_B;
  tensor_B.ctx = dl_context;
  tensor_B.dtype = dl_f32;
  tensor_B.ndim = 1;
  tensor_B.shape = dims;
  tensor_B.strides = nullptr;
  tensor_B.byte_offset = 0;

  DLTensor tensor_C;
  tensor_C.data = arr_C;
  tensor_C.ctx = dl_context;
  tensor_C.dtype = dl_f32;
  tensor_C.ndim = 1;
  tensor_C.shape = dims;
  tensor_C.strides = nullptr;
  tensor_C.byte_offset = 0;

  std::cout << "BEFORE" << std::endl;
  std::cout << "ARRAY A" << std::endl;
  for (auto v : arr_A)
  {
    std::cout << v << std::endl;
  }

  std::cout << "ARRAY B" << std::endl;
  for (auto v : arr_B)
  {
    std::cout << v << std::endl;
  }

  std::cout << "ARRAY C" << std::endl;
  for (auto v : arr_C)
  {
    std::cout << v << std::endl;
  }

  func(&tensor_A, &tensor_B, &tensor_C);

  std::cout << "AFTER" << std::endl;
  std::cout << "ARRAY A" << std::endl;
  for (auto v : arr_A)
  {
    std::cout << v << std::endl;
  }

  std::cout << "ARRAY B" << std::endl;
  for (auto v : arr_B)
  {
    std::cout << v << std::endl;
  }

  std::cout << "ARRAY C" << std::endl;
  for (auto v : arr_C)
  {
    std::cout << v << std::endl;
  }

  return 0;
}

// auto g = nnvm::ApplyPass(graph, "InferShape");
// undefined reference nnvm::ApplyPasses
