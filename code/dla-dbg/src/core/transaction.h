#ifndef __TRANSACTION_H__
#define __TRANSACTION_H__

#include "slot.h"
#include "segment.h"

// TXN abstracts each operation
//
// TXN is an abberivation of "transaction"
struct TXN
{
  struct Context
  {
    virtual ~Context() = default;
    
    // TODO H/W Parameter such as "MAP_L"
        
    virtual std::vector<uint8_t> dla_read(uint32_t base, uint32_t size) const = 0;
    virtual void dla_write(uint32_t base, const std::vector<uint8_t> &data) = 0;

    // TODO Support Write Protection
    // virtual uint32_t dla_protect_set(uint32_t base, uint32_t size) = 0;
    // virtual void dla_protect_unset(uint32_t id) = 0;
  };

  virtual ~TXN() = default;

  // Corresponding slot
  virtual Slot slot(void) const = 0;

  // "begin" is expected to
  // - Insert "Write Protection" if necessary
  // - Read the input values and compute the output
  //   - Note that this output is stored in Transcation itself, and not visible yet.
  virtual void begin(Context *) = 0;

  // "commit" is expected to
  // - Write back the output to memory.
  // - Remove "Write Protection" if it exists, and
  virtual void commit(Context *) = 0;
};

using Transaction = TXN;

#endif // __TRANSACTION_H__
