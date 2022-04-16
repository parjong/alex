#include "code.h"

Code::Code() { }

Code::Code(const hiberlite::sqlid_t& cmd, const std::string& path)
  : cmd_(cmd)
{
  FILE *fp = fopen(path.c_str(), "r");

  load(fp);

  fclose(fp);
}

Code::Code(const hiberlite::sqlid_t& cmd, FILE *fp)
  : cmd_(cmd)
{
  load(fp);
}

Code::~Code() { }

void Code::load(FILE *fp)
{
  rewind(fp);

  while ( 1 )
  {
    char *line = NULL;
    size_t len = 0;

    ssize_t read = getline(&line, &len, fp);

    if ( read == -1 )
    {
      break;
    }

    lines_.push_back(line);

    free(line);
  }
}

hiberlite::sqlid_t Code::cmd(void) const { return cmd_; }
const std::vector<std::string>& Code::lines(void) const { return lines_; }

std::string Code::content(void) const
{
  std::string res;

  for (const std::string& line : lines())
  {
    res += line;
  }

  return res;
}

HIBERLITE_EXPORT_CLASS(Code);
