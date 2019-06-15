#if 0
cin = char stream

take : t stream -> t
valid : t stream -> bool

line_enumerator e{stream}; e.valid(); e.advance()
{

}
#endif

#include <istream>
#include <vector>

namespace
{

struct string_view
{
  string_view(const char *beg, const char *end) : _beg{beg}, _end{end}
  {

  }

  const char *_beg;
  const char *_end;
};

int end_with_eol(const char *beg, size_t len)
{
  if (len == 0)
  {
    return -1;
  }

  return (beg[len - 1] == '\n') ? len - 1 : -1;
}

struct line_enumerator
{
  line_enumerator(std::istream &is) : _is{&is}, _offset{-1}
  {
    advance();
  }

  // data - content[eol] or content[eos]
  //
  // how to detect eol
  // - Linux \n
  // - Windows \r\n

  bool valid(void) const { return _offset != -1; }

  void advance(void)
  {
    _line.clear();

    if (!_is->good())
    {
      _offset = -1;
      return;
    }

    while (_is->good())
    {
      // take one char
      _line.emplace_back(_is->get());

      // check eol
      _offset = end_with_eol(_line.data(), _line.size());
      if (_offset >= 0) break;
    }
  }

  const char *begin() const { return _line.data(); }
  const char *end() const { return _line.data() + _offset; }

  std::istream *_is = nullptr;

  int _offset;
  std::vector<char> _line;
};

} // namespace

#include <iostream>

// csv2html
int main(int argc, char **argv)
{
  uint32_t count = 0;

  for (::line_enumerator e{std::cin}; e.valid(); e.advance())
  {
    std::string s{e.begin(), e.end()};

    std::cout << "LINE " << count++ << ": " << s << std::endl;
  }

  return 0;
}
