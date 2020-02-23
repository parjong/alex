#include "RELU.h"

#include "core/behavior.h"

#include <iostream>

// TODO Use Logging Framework

namespace
{

struct ReluTXN : public TXN
{
  std::vector<uint8_t> out_arr;

  Slot slot(void) const final { return Slot::DLA_COMP; }

  void begin(Context *ctx) final
  {
    std::cout << "Begin Relu transaction" << std::endl;

    // Read 0,0, [0, 64]
    auto inp_arr = ctx->dla_read(0, 64);

    // Compute output
    out_arr.resize(64);

    for (uint32_t n = 0; n < 64; ++n)
    {
      auto inp_value = inp_arr.at(n);
      out_arr.at(n) = inp_value > 128 ? inp_value : 128;
    }

    // write(0, ...);
  }

  void commit(Context *ctx) final
  {
    std::cout << "Commit Relu transaction" << std::endl;
    ctx->dla_write(64, out_arr);
  }
};

struct ReluBM : public InstrBM<Opcode::RELU>
{
  void model(Context *ctx) const final
  {
    if (ctx->ready({Slot::DLA_COMP}))
    {
      std::cout << "Slot is available" << std::endl;
      ctx->enqueue(std::make_unique<ReluTXN>());
    }
    else
    {
      std::cout << "Slot is unavailable" << std::endl;
      ctx->wait();
    }
  }
};

DefaultSystemBM::ExtendWith<ReluBM> ext;

} // namespace
