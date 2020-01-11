#include <sstream>
#include <memory>

namespace Error
{

struct MessageBuffer
{
  private:
    std::stringstream _ss;

  public:
    MessageBuffer(const char *file, int line) : _file(file), _line(line)
    {
      // DO NOTHING
    }

  public:
    std::ostream &stream(void) { return _ss; }

  public:
    ~MessageBuffer()
    {
      _ss << " (from " << _file << ":" << _line << ")";
      throw std::runtime_error(_ss.str());
    }

  private:
    const char *_file;
    const int _line;
};

}

#define CHECK(cond) \
  if (!(cond)) Error::MessageBuffer(__FILE__, __LINE__).stream()

#define CHECK_EQ(lhs, rhs) \
  CHECK((lhs) == (rhs)) << #lhs << " should be same as " << #rhs

int main(int argc, char **argv)
{
  CHECK_EQ(1, 2);

  return 0;
}
