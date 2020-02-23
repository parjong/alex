#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include <cstdint>
#include <map>
#include <memory>
#include <set>
#include <vector>

template<typename T> class Span final
{
public:
  Span() = default;

public:
  Span(T *beg, T *end) : _beg{beg}, _end{end}
  {
    // DO NOTHING
  }

public:
  uint32_t size(void) const { return _end - _beg; }

public:
  T &at(uint32_t off) { return *(_beg + off); }

private:
  T *_beg = nullptr;
  T *_end = nullptr;
};

struct SegmentReadEvent { uint32_t beg; uint32_t end; };
struct SegmentWriteEvent { uint32_t beg; uint32_t end; };

struct SegmentMonitor
{
  virtual ~SegmentMonitor() = default;

  virtual void notify(const SegmentReadEvent &) = 0;
  virtual void notify(const SegmentWriteEvent &) = 0;
};

// TODO Implement monitors
// InvalidWriteMonitor
// UnalignedAccessMonitor
// UninitializedReadMonitor

struct Segment final
{
  Segment(uint32_t size)
  {
    _buf.resize(size);
  }

private: // Raw Data
  std::vector<uint8_t> _buf;

public:
  Span<uint8_t> data(void)
  {
    return Span<uint8_t>{_buf.data(), _buf.data() + _buf.size()};
  }

private: // Attached Monitors
  std::set<std::unique_ptr<SegmentMonitor>> _monitors;

public:
  // attach
  // detach

public:
  std::vector<uint8_t> read(uint32_t addr, uint32_t size) const
  {
    // Check overflow

    // Notify monitors
    {
      SegmentReadEvent evt;

      evt.beg = addr;
      evt.end = addr + size;

      for (const auto &m : _monitors)
      {
        m->notify(evt);
      }
    }

    std::vector<uint8_t> res;

    for (uint32_t n = 0; n < size; ++n)
    {
      res.emplace_back(_buf.at(addr + n));
    }

    return res;
  }

  void write (uint32_t addr, const std::vector<uint8_t> &data)
  {
    // Check overflow

    // Notify monitors
    {
      SegmentWriteEvent evt;

      evt.beg = addr;
      evt.end = addr + data.size();

      for (const auto &m : _monitors)
      {
        m->notify(evt);
      }
    }

    for (uint32_t n = 0; n < data.size(); ++n)
    {
      _buf.at(addr + n) = data.at(n);
    }
  }
};

using SegmentIndex = uint32_t;

#endif // __SEGMENT_H__
