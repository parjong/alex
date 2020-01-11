#ifndef GCC_PARSER_H__
#define GCC_PARSER_H__

#include "emit/emit.h"
#include "emit/command.h"
#include "build/gcc_options.h"

#include <string>
#include <vector>

class GCCCmdlineParser
{
  public:
    class Hook
    {
      public:
        Hook();
        virtual ~Hook();
      public:
        virtual void accept(const std::string& token) = 0;
    };
  public:
    GCCCmdlineParser();
    ~GCCCmdlineParser();
  private:
    std::vector<Hook *> hooks_;
  public:
    void add(Hook *hook);
  public:
    GNUOptions *parse(Emit& emit, hiberlite::sqlid_t id, const Command& cmd);
};

#endif
